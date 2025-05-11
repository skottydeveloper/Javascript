## Description
This is a multi-threaded C program that reads data from a file called "data-1.txt", processes it to remove the header section, and writes the remaining non-header content to a file called "out.txt". The program uses three threads (Thread A, Thread B, and Thread C) and synchronises them using POSIX semaphores and a pipe to communicate and share data between threads.

The program is structured into the following sections:
-  Compilation instructions and header files.
-  Structs, prototypes, and global variables.
-  The main() function.
-  Supporting functions (initializeData(), ThreadA(), ThreadB(), and ThreadC()).

First, the program includes the necessary header files and defines a struct called "ThreadParams" that contains the required parameters for each thread, such as the pipe file descriptors, semaphores, and a message buffer.

Next, the program provides function prototypes for initializeData(), ThreadA(), ThreadB(), and ThreadC(), which are used to implement the core functionality of the program.

The main() function initialises the program by creating a pipe and initialising the semaphores and other resources in the ThreadParams struct. It then creates three threads to execute the ThreadA(), ThreadB(), and ThreadC() functions. Afterward, it waits for the threads to finish their work before closing the pipe and terminating the threads.

The initializeData() function initializes the semaphores, sets up the thread attribute structure, and initialises the global variable "file_read_completed" to 0.

The ThreadA() function reads data from "data-1.txt" and writes each line to a pipe. It uses semaphores to coordinate with Thread C to prevent simultaneous access to the pipe.

The ThreadB() function reads data from the pipe used in ThreadA() and writes it to the message field of the ThreadParams struct. It uses semaphores to coordinate with Thread A (to read from the pipe) and Thread C (to prevent simultaneous access to the message field).

The ThreadC() function reads data from the message field of the ThreadParams struct and writes non-header text to the file "out.txt". It skips the header by checking for the string "end_header". It uses semaphores to coordinate with Threads A and B to prevent simultaneous access to the pipe and the message field.

In summary, this program demonstrates the use of multi-threading, pipes, and semaphores to read data from a file, process it, and write the result to another file in a synchronised and concurrent manner.

## Instructions

Thanks to the use of a makefile, it's easy to compile and run the the multi-threaded file processor program. The instructions are as of below:
1.  Ensure that gcc is installed.
2.  Run the following command: "make".
3.  Type: "./prog_1".
4.  To clean all output files created, run "make clean".
