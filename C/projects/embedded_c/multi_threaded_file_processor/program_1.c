/***********************************************************************************************************
 * Compilation instructions:
 * To compile "program_1", ensure that gcc is installed.
 * Run the following command: "make", then type: "./program_1".
 * To clean all output files created, run "make clean".
************************************************************************************************************/

/***********************************************************************************************************
 * List of header files used.
************************************************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/time.h>

/***********************************************************************************************************
 * List of structs used.
************************************************************************************************************/
typedef struct ThreadParams {
  int pipeFile[2];
  sem_t sem_A, sem_B, sem_C;
  char message[255];
} ThreadParams;

/***********************************************************************************************************
 * List of prototypes used.
************************************************************************************************************/
/* Initializes data and utilities used in thread params. */
void initializeData(ThreadParams *params);

/* This thread reads data from data.txt and writes each line to a pipe. */
void* ThreadA(void *params);

/* This thread reads data from pipe used in ThreadA and writes it to a shared variable. */
void* ThreadB(void *params);

/* This thread reads from shared variable and outputs non-header text to out.txt. */
void* ThreadC(void *params);

/***********************************************************************************************************
 * List of global variables used.
************************************************************************************************************/
// Global variable to store thread attribute data, used for thread creation.
pthread_attr_t attr;

// Global variable to store the state of the end of the file, used for synchronisation between threads.
int file_read_completed;

/***********************************************************************************************************
* The main() function.                               
************************************************************************************************************/
int main(int argc, char const *argv[]) {
  int pipe_result;

  pthread_t tid[3];

  ThreadParams params;
  
  // Initialisation.
  initializeData(&params);
  
  // Create the pipe.
  pipe_result = pipe(params.pipeFile);
  
  if (pipe_result < 0) {
    perror("Pipe error.");
    exit(1);
  }

  /* Create a new thread for each function using "pthread_create()". If there's an error creating any of 
  the threads, the program will print an error message and exit with a -1 status code. */  
  void* (*thread_functions[3])(void*) = {ThreadA, ThreadB, ThreadC};

  for (int i = 0; i < 3; i++) {
    if (pthread_create(&tid[i], &attr, thread_functions[i], (void*)(&params)) != 0) {
        perror("Error creating threads: ");
        exit(-1);
    }
  }

  // Wait on the threads to finish and exit.
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  
  // Close the pipes.
  close(params.pipeFile[0]);
  close(params.pipeFile[1]);

  // Terminate the thread execution for each of the three threads.
  pthread_cancel(tid[0]);
  pthread_cancel(tid[1]);
  pthread_cancel(tid[2]);

  return 0;
}

/************************************************************************************************************
 * initializeData() function description: 
 * The 'initializeData()' function involves initialising the semaphores, which are used to synchronize access
 * to shared resources between the three threads.
 *
 * Inputs:
 * - A pointer to a ThreadParams struct.
 *
 * Outputs:
 * - The ThreadParams struct is modified in-place with initialised semaphores.
************************************************************************************************************/
void initializeData(ThreadParams *params) {
  /* Initialise the named "sem_A", 0-shared between threads, initial value is set to one = 1. */
  sem_init(&(params->sem_A), 0, 1);
  
  /* Initialise the named "sem_B", 0-shared between threads, initial value is set to two = 0. */
  sem_init(&(params->sem_B), 0, 0);
  
  /* Initialize the named "sem_C", 0-shared between threads, initial value is set to three = 0. */
  sem_init(&(params->sem_C), 0, 0);

  // Initialise the thread attributes, to get the default properties. 
  pthread_attr_init(&attr);

  // Set the end of the file value to 0, and initialise it.
  file_read_completed = 0; 

  return;
}

/************************************************************************************************************
 * ThreadA() function description: 
 * The 'ThreadA()' function involves Thread A reading data from the file "data.txt" and writing each line to 
 * a pipe. It uses a semaphore to coordinate with Thread C to prevent simultaneous access to the pipe.
 *
 * Inputs:
 * - A pointer to a ThreadParams struct cast to void*.
 *
 * Outputs:
 * - Reads data from "data-1.txt" and writes each line to a pipe. 
 * - This function has no direct return value, as it's a pthread function, so it returns NULL.
************************************************************************************************************/
void* ThreadA(void *params) {
  // Cast "params" to "ThreadParams".
  ThreadParams *threadA_params = (ThreadParams *)(params);
  
  // "data-1.txt" is defined and stored into a local variable filename.
  static const char file[] = "data-1.txt"; 

  // Open the input file for reading.
  FILE *fReader; 
  
  // Validation check.
  if ((fReader = fopen(file, "r")) == NULL) {
    printf("Error in opening file!");
    exit(-1);
  }

  do {
    // Wait for semaphore A to finish.
    sem_wait(&(threadA_params->sem_A));

    // Read the file.
    if (fgets(threadA_params->message, sizeof(threadA_params->message), fReader) == NULL) {
      // Set "file_read_completed" flag to 1, after fully reading the file.
      file_read_completed = 1;

      // Signal semaphore C.
      sem_post(&(threadA_params->sem_C));

      break;
    }

    // Write the data from the file to the pipe.
    write(threadA_params->pipeFile[1], threadA_params->message, strlen(threadA_params->message) + 1);

    // Signal semaphore C.
    sem_post(&(threadA_params->sem_C));
  } while (!file_read_completed);

  // Close the write end of the pipe.
  close(threadA_params->pipeFile[1]);

  // Close the input file.
  fclose(fReader); 

  return NULL;
}

/************************************************************************************************************
 * ThreadB() function description: 
 * The 'ThreadB()' function involves Thread B reading data from the pipe used in Thread A and writes it to 
 * the message field of the ThreadParams struct. It uses semaphores to coordinate with Thread A 
 * (to read from the pipe) and Thread C (to prevent simultaneous access to the message field).
 *
 * Inputs:
 * - A pointer to a ThreadParams struct cast to void*.
 *
 * Outputs:
 * - Reads data from the pipe and writes it to the message field of the ThreadParams struct. 
 * - This function has no direct return value, as it's a pthread function, so it returns NULL.
************************************************************************************************************/
void* ThreadB(void *params) {
  // Cast "params" to ThreadParams.
  ThreadParams *threadB_params = (ThreadParams *)(params);

  do {
    // Wait for semaphore C to finish.
    sem_wait(&(threadB_params->sem_C));

    // Read data from the pipe and store it in the message field.
    read(threadB_params->pipeFile[0], threadB_params->message, sizeof(threadB_params->message));

    // Signal semaphore B.
    sem_post(&(threadB_params->sem_B));

    // Check if the end of the file is reached.
    if (file_read_completed == 1) {
        break;
    }
  } while (!file_read_completed);

  // Close the read end of the pipe.
  close(threadB_params->pipeFile[0]); 
  
  return NULL;
}

/************************************************************************************************************
 * ThreadC() function description: 
 * The 'ThreadC()' function involves Thread C reading data from the message field of the ThreadParams struct 
 * and writes non-header text to the file "out.txt". It skips the header by checking for the string 
 * "end_header". It uses semaphores to coordinate with Threads A and B to prevent simultaneous access 
 * to the pipe and the message field.
 *
 * Inputs:
 * - A pointer to a ThreadParams struct cast to void*.
 *
 * Outputs:
 * - Reads data from the message field of the ThreadParams struct and writes non-header text to "out.txt". 
 * - This function has no direct return value, as it's a pthread function, so it returns NULL.
************************************************************************************************************/
void* ThreadC(void *params) {
  // Cast "params" to ThreadParams.
  ThreadParams *threadC_params = (ThreadParams *)(params);
  
  // Initialise the header processed checker to track if the header has been processed.
  int header_processed = 0; 

  // "out.txt" is defined and stored into a local variable filename.
  static const char file[] = "out.txt"; 

  // Open the output file for writing.
  FILE *fWriter;

  // Validation check.
  if ((fWriter = fopen(file, "w")) == NULL) {
    printf("Error in opening file!");
    exit(-1);
  }

  do {
    // Wait for semaphore B to be signaled before proceeding.
    sem_wait(&(threadC_params->sem_B));

    // If the header has been processed, write non-header lines to the output file.
    if (header_processed) {
      // Write non-header lines to the output file.
      fputs(threadC_params->message, fWriter);

      // Break the loop if the end of the file is reached.
      if (file_read_completed == 1) {
          break;
      }
    }
    // If the header has not been processed, look for the end of the header.
    else {
      // Find the "end_header" substring in the current message.
      char *header_end = strstr(threadC_params->message, "end_header");
      
      // If the "end_header" substring is found, set the "header_processed" flag.
      if (header_end) {
        // Set the flag to indicate that the header has been processed.
        header_processed = 1;
      }
    }

    // Signal semaphore A.
    sem_post(&(threadC_params->sem_A));
  } while (!file_read_completed);

  // Close the output file.
  fclose(fWriter); 
  
  return NULL;
}