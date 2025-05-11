# C
## Summary
This repository is a portfolio of code for the C programming language. It consists of projects I have completed, during uni and in my own time, while learning C.

## Mini-Projects & Exercises
Consists of basic, miniature projects and exercises that demonstrate my knowledge in each feature of the C programming language. For example, one project will demonstrate the application of knowledge in pointers and structures, while another will demonstrate the application of knowledge in switch statements.

## Notable Projects
### Payroll Management System
#### Summary
Keeping track of payment information is a hassle. Payment statements can be long, spread across multiple files which takes up storage and contain information such as bank addresses, residential addresses, payment amounts and other sensitive data. Working in a team of two, we created a payment information system to allow the user to keep track of their information.

#### Link
https://github.com/skottydeveloper/C/tree/main/projects/payment_mangement_system

### Multi-Threaded File Processor
#### Summary
A multi-threaded C program that reads data from "data-1.txt", processes it to remove headers, and writes non-header content to "out.txt". It utilises three threads (A, B, and C), POSIX semaphores, and a pipe for synchronization and data sharing. Thread A reads from the input file and writes to the pipe; Thread B reads from the pipe and stores data in the message field of the shared ThreadParams struct; Thread C reads from the message field and writes non-header data to the output file. The program demonstrates the use of multi-threading, pipes, and semaphores for synchronised and concurrent data processing.

#### Link
https://github.com/skottydeveloper/C/tree/main/projects/embedded_c/multi_threaded_file_processor
