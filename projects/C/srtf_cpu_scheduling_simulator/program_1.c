/******************************************************************************
 * Compilation instructions:
 * To compile "program_1", ensure that gcc and make is installed.
 * Run the following command: "make run_prog_1".
 * To clean all output files created, run "make clean".
******************************************************************************/
/******************************************************************************
 * List of header files used.
******************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>

/******************************************************************************
 * List of structs used.
******************************************************************************/
typedef struct SRTF_Params {
    int process_id;
    float arrive_time;
    float wait_time;
    float burst_time;
    float turnaround_time;
    float remaining_burst_time;
} Process_Params;

/******************************************************************************
 * List of global variables used.
******************************************************************************/
float avg_wait_time = 0.0; 
float avg_turnaround_time = 0.0;

sem_t sem_SRTF;

pthread_t processor; 
pthread_t writer;

/******************************************************************************
 * List of macro definitions used.
******************************************************************************/
#define PROCESS_NUMBER 7
#define OUTPUT_FILE_NAME "output.txt"
#define FIFO_NAME "/tmp/myfifo1"

/******************************************************************************
 * List of function prototypes used.
******************************************************************************/
void *worker1(void *params);
void *worker2();

/******************************************************************************
 * 'worker1()' function description:
    This function simulates the SRTF (Shortest Remaining Time First) CPU 
    scheduling algorithm. It calculates the average waiting time and 
    average turnaround time of the worker_processes and writes the data 
    to a named pipe (FIFO).
 
 * Inputs: 
    * A void pointer to an array of Process_Params structs (cast to void*).
 
 * Outputs: 
    * The waiting time and turn-around time are written to the FIFO.
******************************************************************************/
void *worker1(void *params) {
  /* Cast input parameter to the 'Process_Params' struct. */
  Process_Params *worker_processes = (Process_Params *)params;

  /* Initialise the CPU time counter. */
  int cpu_time = 0;

  /* Initialise the total wait time counter. */
  float total_wait_time = 0;

  /* Initialise the total turnaround time counter. */
  float total_turn_around_time = 0;
  
  /* Initialise the index of the shortest remaining time process. */
  int index_srt = 0;

  /* Initialise the number of completed worker processes. */
  int num_worker_processes_complete = 0;
  
  /* Loop until all worker processes are completed. */
  while (num_worker_processes_complete != PROCESS_NUMBER) {
    /* Reset the index of the shortest remaining time process. */
    index_srt = -1;

    /* Initialise a flag to check if a process is found. */
    bool is_found = false;

    /* Loop through all the worker processes. */
    for (int i = 0; i < PROCESS_NUMBER; i++) {
      /* Check if the process has arrived and still has remaining burst time. */
      if (cpu_time >= worker_processes[i].arrive_time && worker_processes[i].remaining_burst_time > 0) {
        /* Update the index of the shortest remaining time process. */
        if (!is_found || worker_processes[i].remaining_burst_time < worker_processes[index_srt].remaining_burst_time) {
          index_srt = i;
          is_found = true;
        }
      }
    }
    
    /* Increment the CPU time counter. */
    cpu_time++;

    /* Decrement the remaining burst time of the chosen process. */
    worker_processes[index_srt].remaining_burst_time -= 1;

    /* Check if the chosen process has completed its burst time. */
    if (worker_processes[index_srt].remaining_burst_time == 0) {
      /* Calculate the wait time and turnaround time for the completed process. */
      worker_processes[index_srt].wait_time = cpu_time - worker_processes[index_srt].arrive_time - worker_processes[index_srt].burst_time;
      total_wait_time +=  worker_processes[index_srt].wait_time;
      
      worker_processes[index_srt].turnaround_time = cpu_time - worker_processes[index_srt].arrive_time;
      total_turn_around_time +=  worker_processes[index_srt].turnaround_time;
      
      /* Increment the number of completed worker processes. */
      num_worker_processes_complete++;
    }
  }
  
  /* Calculate the average wait time and average turnaround time. */
  avg_wait_time = total_wait_time / PROCESS_NUMBER;
  avg_turnaround_time = total_turn_around_time / PROCESS_NUMBER; 

  /* Print the process schedule table and average wait and turnaround times. */
  printf("Process Schedule Table: \n");
  printf("\tProcess ID:\tArrival Time:\tBurst Time:\tWait Time:\tTurnaround Time:\n");
  
  for (int i = 0; i < PROCESS_NUMBER; i++) {
    printf("\t%d\t\t%f\t%f\t%f\t%f\n", worker_processes[i].process_id, worker_processes[i].arrive_time, worker_processes[i].burst_time, worker_processes[i].wait_time, worker_processes[i].turnaround_time);
  }

  printf("Average wait time of each process: %0.4fs\n", avg_wait_time);
  printf("Average turnaround time of each process: %0.4fs\n", avg_turnaround_time);

  /* Create and open the FIFO for writing. */
  int result;
  int fifo_file_descriptor;

  if ((result = mkfifo(FIFO_NAME, 0777)) < 0) {
    fprintf(stderr, "mkfifo() error!\n");
    exit(EXIT_FAILURE);
  }

  /* Post the semaphore to signal the writer thread. */
  if (sem_post(&sem_SRTF) == -1) {
    fprintf(stderr, "Semaphore unlocking error!\n");
    exit(EXIT_FAILURE);
  }

  /* Open the FIFO for writing. */
  if ((fifo_file_descriptor = open(FIFO_NAME, O_WRONLY)) < 0) {
    fprintf(stderr, "FIFO open sending error!\n");
    exit(EXIT_FAILURE);
  }

  /* Write the average wait time to the FIFO. */
  if (write(fifo_file_descriptor, &avg_wait_time, sizeof(avg_wait_time)) == -1) {
    fprintf(stderr, "Cannot write to FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Write the average turnaround time to the FIFO. */
  if (write(fifo_file_descriptor, &avg_turnaround_time, sizeof(avg_turnaround_time)) == -1) {
    fprintf(stderr, "Cannot write to FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Close the FIFO file descriptor. */
  if (close(fifo_file_descriptor) == -1) {
    fprintf(stderr, "Cannot close FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Return NULL since the function has a void* return type. */
  return NULL;
}

/******************************************************************************
 * worker2() function description:
  This function reads the average waiting time and average turnaround time 
  from the named pipe (FIFO) and writes the data to an output text file.

 * Inputs: 
    * None.
 
 * Outputs: 
    * The waiting time and turn-around time are read from the FIFO and 
      written to a text file.
******************************************************************************/
void *worker2() {
  /* Wait for the semaphore to be posted by 'worker1()'. */
  if (sem_wait(&sem_SRTF) == -1) {
    fprintf(stderr, "Semaphore lock error!\n");
    exit(EXIT_FAILURE);
  }
  
  /* File descriptor for the FIFO. */
  int fifo_file_descriptor;

  /* Average turnaround time read from the FIFO. */
  float fifo_avg_turnaround_time; 

  /* Average wait time read from the FIFO. */
  float fifo_avg_wait_time;

  /* Open the FIFO for reading. */
  if ((fifo_file_descriptor = open(FIFO_NAME, O_RDONLY)) < 0) {
    fprintf(stderr, "FIFO open read error!\n");
    exit(EXIT_FAILURE);
  }

  /* Read the average wait time from the FIFO. */
  if (read(fifo_file_descriptor, &fifo_avg_wait_time, sizeof(int)) == -1) {
    fprintf(stderr, "Cannot read from FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Read the average turnaround time from the FIFO. */
  if (read(fifo_file_descriptor, &fifo_avg_turnaround_time, sizeof(int)) == -1) {
    fprintf(stderr, "Cannot read from FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Close the FIFO file descriptor. */
  if (close(fifo_file_descriptor) == -1) {
    fprintf(stderr, "Cannot close named FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* Remove the FIFO file. */
  if (remove(FIFO_NAME) == -1) {
    fprintf(stderr, "Cannot remove named FIFO!\n");
    exit(EXIT_FAILURE);
  }

  /* File pointer for the output file. */
  FILE *file_to_write;

  /* Open the output file for writing. */
  if ((file_to_write = fopen(OUTPUT_FILE_NAME, "w")) == NULL) {
    fprintf(stderr, "Error in opening file!");
    exit(EXIT_FAILURE);
  }

  /* Write the average wait time and average turnaround time to the output file. */
  fprintf(file_to_write, "Average wait time: %fs\n", fifo_avg_wait_time);
  fprintf(file_to_write, "Average turnaround time: %fs", fifo_avg_turnaround_time);

  /* Close the output file. */
  if (fclose(file_to_write) != 0) {
    fprintf(stderr, "Error in closing stream!");
    exit(EXIT_FAILURE);
  }

  /* Return NULL since the function has a void* return type. */
  return NULL;
}

/******************************************************************************
 * 'main()' function description:
    The main function initialises the shared data, creates and initialises the 
    semaphores, and spawns two threads (processor and writer). 
    It waits for both threads to complete and then cleans up resources.
 
 * Inputs: 
    * None.

 * Outputs: 
    * Returns 0 on successful execution.
******************************************************************************/                            
int main(void) {
  /* Cast pointer to the 'Process_Params' struct. */
  Process_Params *worker_processes;

  /* Allocate memory for the 'worker_processes' array, 
  sized based on the number of processes. */
  worker_processes = malloc(sizeof(Process_Params) * PROCESS_NUMBER);

  /* Check if memory allocation was successful. 
  If not, print an error message and exit. */
  if (worker_processes == NULL) {
    fprintf(stderr, "Error in allocating memory!\n");
    exit(EXIT_FAILURE);
  }

  /* Initialise 'worker_processes' array with process information, 
  including process ID, arrival time, burst time, and remaining burst time. */
  worker_processes[0].process_id = 1; 
  worker_processes[0].arrive_time = 8; 
  worker_processes[0].burst_time = 10; 
  worker_processes[0].remaining_burst_time = 10;

  worker_processes[1].process_id = 2; 
  worker_processes[1].arrive_time = 10; 
  worker_processes[1].burst_time = 3; 
  worker_processes[1].remaining_burst_time = 3;
  
  worker_processes[2].process_id = 3; 
  worker_processes[2].arrive_time = 14; 
  worker_processes[2].burst_time = 7; 
  worker_processes[2].remaining_burst_time = 7;
  
  worker_processes[3].process_id = 4; 
  worker_processes[3].arrive_time = 9; 
  worker_processes[3].burst_time = 5;  
  worker_processes[3].remaining_burst_time = 5;
  
  worker_processes[4].process_id = 5; 
  worker_processes[4].arrive_time = 16; 
  worker_processes[4].burst_time = 4; 
  worker_processes[4].remaining_burst_time = 4;
  
  worker_processes[5].process_id = 6; 
  worker_processes[5].arrive_time = 21; 
  worker_processes[5].burst_time = 6; 
  worker_processes[5].remaining_burst_time = 6;
  
  worker_processes[6].process_id = 7; 
  worker_processes[6].arrive_time = 26; 
  worker_processes[6].burst_time = 2; 
  worker_processes[6].remaining_burst_time = 2;

  /* Initialise the semaphore 'sem_SRTF' with an initial value of 0. */
  if (sem_init(&sem_SRTF, 0, 0) != 0) {
    fprintf(stderr, "Semaphore initialisation error!\n");
    exit(EXIT_FAILURE);
  }

  /* Create the processor (worker1) thread, passing the 
  'worker_processes' array as an argument. */
  if (pthread_create(&processor, NULL, worker1, (void *)worker_processes) != 0) {
    fprintf(stderr, "Processor thread creation error!\n");
    exit(EXIT_FAILURE);
  }

  /* Create the writer (worker2) thread, not passing any arguments. */
  if (pthread_create(&writer, NULL, (void *)worker2, NULL) != 0) {
    fprintf(stderr, "Writer thread creation error!\n");
    exit(EXIT_FAILURE);
  }

  /* Wait for the processor (worker1) thread to finish 
  execution and join it back to the main thread. */
  if (pthread_join(processor, NULL) != 0) {
    fprintf(stderr, "Join processor thread error!\n");
    exit(EXIT_FAILURE);
  }

  /* Wait for the writer (worker2) thread to finish 
  execution and join it back to the main thread. */
  if (pthread_join(writer, NULL) != 0) {
    fprintf(stderr, "Join writer thread error!\n");
    exit(EXIT_FAILURE);
  }

  /* Destroy the semaphore 'sem_SRTF', freeing any resources it holds. */
  if (sem_destroy(&sem_SRTF) != 0) {
    fprintf(stderr, "Semaphore destruction error.\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}