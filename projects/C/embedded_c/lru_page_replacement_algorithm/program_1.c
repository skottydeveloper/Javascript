/******************************************************************************************************************************************************************************************************
 * Compilation instructions:
 * To compile "program_1", ensure that gcc and make is installed.
 * Run the following command: "make run_prog_1".
 * To clean all output files created, run "make clean".
******************************************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************************************
 * List of header files used.
******************************************************************************************************************************************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

/******************************************************************************************************************************************************************************************************
 * List of macro definitions used.
******************************************************************************************************************************************************************************************************/
#define REFERENCESTRINGLENGTH 24

/******************************************************************************************************************************************************************************************************
 * List of global variables used.
******************************************************************************************************************************************************************************************************/
// Number of page faults in the program.
int page_faults = 0;

/******************************************************************************************************************************************************************************************************
 * List of function prototypes used.
******************************************************************************************************************************************************************************************************/
void SignalHandler(int signal);

/******************************************************************************************************************************************************************************************************
* 'main()' function description:
  This function is the main routine for the program. It is in charge of setting up the threads and the FIFO. It initialises the frame with empty values and processes the reference string. 
  The program will run until a SIGINT signal (Ctrl+C) is received.

* Inputs:
	* Number of arguments passed to the program (argc).
	* Array of values passed to the program (argv).

* Outputs:
	* Returns 0 upon completion.
******************************************************************************************************************************************************************************************************/
int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Please give an argument (i.e. the number of frames).\n");
		exit(-1);
	}

	// Parse the argument provided from the user on the frame size.
	int frame_size = atoi(argv[1]);

	if (frame_size <= 0) {
		printf("Please give a valid number that's larger than zero.\n");
		exit(-1);
	}

	// Register Ctrl+C (SIGINT) signal and call the signal handler for the function.
	signal(SIGINT, SignalHandler);

	// Declare and initialise the 'frame' array.
	uint frame[frame_size];
	
	int ref_string[REFERENCESTRINGLENGTH] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1, 7, 5};
	
	// Next position to write a new value to.
	int next_write_position = 0;

	// Current value of the reference string.
	int current_value;

	// Declare and initialise the 'time_since_last_access' array.
	unsigned int time_since_last_access[frame_size];

	// Set initial values for the 'frame' and 'time_since_last_access' arrays.
	for (int i = 0; i < frame_size; i++) {
		time_since_last_access[i] = 0;
		frame[i] = -1;
	}

	// Loop through the reference string values.
	for (int i = 0; i < REFERENCESTRINGLENGTH; i++) {
		current_value = ref_string[i];

		// Boolean value for whether there is a match or not.
		bool match = false;

		// Check if the current value is already in the frame.
		for (int k = 0; k < frame_size; k++) {
			if (frame[k] == current_value) {
				match = true;
				break;
			}
		}

		// If the value is not in the frame, find the next position to write and update the frame.
		if (!match) {
			int least_recently_used_index = 0;

			// Find the index with the maximum 'time_since_last_access' value.
			for (int k = 0; k < frame_size; k++) {
				if (time_since_last_access[k] > time_since_last_access[least_recently_used_index]) {
					least_recently_used_index = k;
				}
			}

			// Determine the 'next_write_position' based on whether the current slot is empty or not.
			if (frame[i % frame_size] == -1) {
				next_write_position = i % frame_size;
			} else {
				next_write_position = least_recently_used_index;
			}

			// Update the 'frame' and 'time_since_last_access' arrays.
			frame[next_write_position] = current_value;
			time_since_last_access[next_write_position] = 0;

			// Increment the number of page faults.
			page_faults++;
    	}

		// Increment the 'time_since_last_access' values for all other slots in the frame.
		for (int j = 0; j < frame_size; j++) {
			if (frame[j] != -1 && j != next_write_position) {
				time_since_last_access[j]++;
			}
		}

		// Print the current state of the frame.
		printf("Frame State at Iteration %d: [", i + 1);

		for (int k = 0; k < frame_size; k++) {
			printf("%d", frame[k]);
		
			if (k < frame_size - 1) {
				printf(", ");
			}
		}

		printf("]\n");
	}

	// Keep the program running until the 'Ctrl+C' signal is given by the user.
	while (1) {
		sleep(1);
	}

	return 0;
}

/******************************************************************************************************************************************************************************************************
* 'SignalHandler()' function description:
  This function is called when a signal is received by the program. It prints the total number of page faults and exits the program.

* Inputs:
	* An integer value for the signal passed to the function.

* Outputs:
	* Prints the total number of page faults.
	* Exits the program.
******************************************************************************************************************************************************************************************************/
void SignalHandler(int signal) {
	if (signal == SIGINT) {
		printf("\nTotal page faults: %d\n", page_faults);
		exit(0);
	}
}