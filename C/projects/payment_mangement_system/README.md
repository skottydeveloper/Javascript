## Description
The Payment Information System secures and simplifies the storage of payment records for a digital marketing company. The company receives payment from a client for services provided. The client provides the company with information such as their bank account information, mailing address, business name, and date of payment. At the time of entry, these details are compressed and saved to a linked list. The business manager can use the program to encrypt this data and save it to a text file outside the linked list, allowing for payment records to be kept while ensuring delicate information security. At any point in time the manager can decrypt the files for momentary viewing and then discard this file later, maintaining security of the client's information.

## Instructions
Thanks to the use of a makefile, it's easy to compile and run the the payroll management system program. The instructions are as of below:
1. In the terminal, type: "make clean". This will delete all the loaded files from the makefile's cache. 
2. In the terminal, then type: "make SecurePayroll.out". This will add all the loaded files to the makefile's cache.
3. To run the program, you need to supply a command line argument, this is either done by "./SecurePayroll.out -r" for user mode (allows you to run the program as per normal), or "./SecurePayroll.out -d" for debug mode (allows you to see additional things being printed, while going through all of the program's functionalities). 
