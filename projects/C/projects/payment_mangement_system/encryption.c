/******************************************************************************
 * List of header files used.
******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedListSource.h"
#include "compression.h"

/*******************************************************************************
 * The function prototypes used.
*******************************************************************************/
void encryptStringandAdd(char string[], FILE *fptt);

/******************************************************************************
 * encryptAll() function description:
 * The 'encryptAll()' function firstly opens a file, and writes to it - all of
 * the clients' information to it. The clients' information is then encrypted
 * into text - via the 'encryptStringandAdd()' function. While the text is 
 * being written to the file, it's also being compressed. When all the text 
 * is written to the file, in its encrypted form - it's then decompressed.  
 *
 * Inputs:
 * - 'customerID' from the 'client' struct.
 * - 'name' from the 'client' struct.
 * - 'business_name' from the 'client' struct.
 * - 'amount_paid' from the 'client' struct.
 * - 'bank_account' from the 'client' struct.
 * - 'date_of_payment' (day, month, year) from the 'client' struct.
 * - 'invoice_number' from the 'client' struct.
 *
 * Outputs:
 * - The encrypted 'customerID'.
 * - The encrypted 'name'.
 * - The encrypted 'business_name'.
 * - The encrypted 'amount_paid'.
 * - The encrypted 'bank_account'.
 * - The encrypted 'date_of_payment'.
 * - The encrypted 'invoice_number'.
******************************************************************************/
void encryptAll() {
	FILE *fptt;
	int i;	

	/* Open and write to a new file, named "Payment_Summary". */
	fptt = fopen("Payment_Summary", "w");

	/* If the desired file cannot be created correctly. */
    if (fptt == NULL) {
		printf("Error in creation of file!");
		fclose(fptt);
		exit(2);
	}

	for (i = 0; i < size() + 1; i++) {
		/* Get each client. */
		client_t client = getClient(i); 

		/* Strings to store final data to encrypt. */
		char stringInvoiceNo[200], stringCustomerID[200], stringName[200];
		char stringBusinessName[200], stringBankAccountNumber[200];
		char stringDate[200], stringAmountPaid[200];

		/* Compressing headings to save memory. Concantenating data
		with headings which are decompressed and transforming 
		everything to a string: */
		char* heading = "Invoice Number: ";
		heading = compress(heading);
		sprintf(stringInvoiceNo, "%s%d\n", decompress(heading), 
		client.invoice_number);

		heading = "Customer ID: ";
		heading = compress(heading);
		sprintf(stringCustomerID, "%s%d\n", decompress(heading), 
		client.customerID);

		heading = "Name: ";
		heading = compress(heading);
		sprintf(stringName, "%s%s\n", decompress(heading), 
		decompress(client.name));

		heading = "Business Name: ";
		heading = compress(heading);
		sprintf(stringBusinessName, "%s%s\n", decompress(heading), 
		decompress(client.business_name));

		heading = "Bank Account Number: ";
		heading = compress(heading);
		sprintf(stringBankAccountNumber, "%s%s\n",
		decompress(heading), client.bank_account);
		
		heading = "Date of Payment: ";
		heading = compress(heading);
		sprintf(stringDate, "%s%d-%d-%d\n\n", 
		decompress(heading),
		client.date_of_payment.day, client.date_of_payment.month, 
		client.date_of_payment.year);

		heading = "Amount to Pay: ";
		heading = compress(heading);
		sprintf(stringAmountPaid, "%s%d\n", decompress(heading), 
		client.amount_paid);

		/* Encrypt each piece of data and write it to the file. */
		encryptStringandAdd(stringInvoiceNo, fptt);
		encryptStringandAdd(stringCustomerID, fptt);
		encryptStringandAdd(stringName, fptt);
		encryptStringandAdd(stringBusinessName, fptt);
		encryptStringandAdd(stringBankAccountNumber, fptt);
		encryptStringandAdd(stringAmountPaid, fptt);
		encryptStringandAdd(stringDate, fptt);
	}

	/* Close the file, after encrypting it. */
	fclose(fptt);
	printf("File Payment_Summary is successfully encrypted!\n\n");	
}

/******************************************************************************
 * encryptSpecific() function description: 
 * The 'encryptSpecific()' function firstly opens a file, and writes to 
 * it - all of the specified client's information to it. The clients' 
 * information is then encrypted into text - via the 'encryptStringandAdd()' 
 * function. While the text is being written to the file, it's also being 
 * compressed. When all the text is written to the file, in its encrypted 
 * form - it's then decompressed.
 *
 * Inputs:
 * - 'customerID' from the 'client' struct.
 * - 'name' from the 'client' struct.
 * - 'business_name' from the 'client' struct.
 * - 'amount_paid' from the 'client' struct.
 * - 'bank_account' from the 'client' struct.
 * - 'date_of_payment' (day, month, year) from the 'client' struct.
 * - 'invoice_number' from the 'client' struct.
 *
 * Outputs:
 * - The encrypted 'customerID'.
 * - The encrypted 'name'.
 * - The encrypted 'business_name'.
 * - The encrypted 'amount_paid'.
 * - The encrypted 'bank_account'.
 * - The encrypted 'date_of_payment'.
 * - The encrypted 'invoice_number'.
******************************************************************************/
void encryptSpecific() {
	FILE *fptt;
	char selectedBusiness[100];
	int businessFound, i, indexes[100], indexSize = 0;

	/* Allow user to input their business name in. */
    printf("Please type the business to create a payment summary for: ");
	scanf("%s", selectedBusiness);

	for (i = 0; i < size() + 1; i++) {
		/* Get each client. */
		client_t client = getClient(i);
		char *businessNameP = client.business_name;
		
		/* If the business name inputted, matches the business name in the 
		file of clients' information. */
		if (strcmp(businessNameP, selectedBusiness) == 0) {
			businessFound = 1;
			indexes[indexSize] = i;
			indexSize++;
		}
	}

	/* If the business name inputted, doesn't match the business name in the 
	file of clients' information. */
	if (businessFound == 0) {
		printf("Business could not be found, exiting...\n\n");
	} else {
        printf("Business was found,creating encrypted document\n\n");
		fptt = fopen(selectedBusiness, "w");
	
		/* If the file cannot be created correctly. */
		if (fptt == NULL) {
			printf("Error in creation of file!");
			fclose(fptt);
			exit(2);
		}

		for (i = 0; i < indexSize; i++) {
			/* Get each client. */
			client_t client = getClient((indexes[i]));

			/* Strings to store final data to encrypt. */
			char stringInvoiceNo[200], stringCustomerID[200], stringName[200];
			char stringBusinessName[200], stringBankAccountNumber[200];
			char stringDate[200], stringAmountPaid[200];

			/* Compressing headings to save memory. Concantenating data
			with headings which are decompressed and transforming 
			everything to a string: */
			char* heading = "Invoice Number: ";
			heading = compress(heading);
			sprintf(stringInvoiceNo, "%s%d\n", decompress(heading), 
			client.invoice_number);

			heading = "Customer ID: ";
			heading = compress(heading);
			sprintf(stringCustomerID, "%s%d\n", decompress(heading), 
			client.customerID);

			heading = "Name: ";
			heading = compress(heading);
			sprintf(stringName, "%s%s\n", decompress(heading), client.name);

			heading = "Business Name: ";
			heading = compress(heading);
			sprintf(stringBusinessName, "%s%s\n", decompress(heading),
			client.business_name);

			heading = "Bank Account Number: ";
			heading = compress(heading);
			sprintf(stringBankAccountNumber, "%s%s\n",
			decompress(heading), client.bank_account);
			
			heading = "Date of Payment: ";
			heading = compress(heading);
			sprintf(stringDate, "%s%d-%d-%d\n\n", 
			decompress(heading),
			client.date_of_payment.day, client.date_of_payment.month, 
			client.date_of_payment.year);
			
			heading = "Amount to Pay: ";
			heading = compress(heading);
			sprintf(stringAmountPaid, "%s%d\n", decompress(heading), 
			client.amount_paid);

			/* Encrypt each piece of data and write it to the file. */
			encryptStringandAdd(stringInvoiceNo, fptt);
			encryptStringandAdd(stringCustomerID, fptt);
			encryptStringandAdd(stringName, fptt);
			encryptStringandAdd(stringBusinessName, fptt);
			encryptStringandAdd(stringBankAccountNumber, fptt);
			encryptStringandAdd(stringAmountPaid, fptt);
			encryptStringandAdd(stringDate, fptt);
		}

		/* Close the file, after encrypting it. */
		fclose(fptt);
    }	
}

/******************************************************************************
 * encryptStringandAdd() function description:
 * The 'encryptStringandAdd()' function takes the clients' information, and 
 * encrypts it into text that's unreadable to anyone that isn't the person 
 * who encrypted it.
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void encryptStringandAdd(char string[], FILE *fptt) {
	int j;

	for (j = 0; j < strlen(string); j++) {
		/* For each character in the string, encrypt it by adding 100 to the 
		ASCII character index - so that the end product is
		the whole string being encrypted. */
		char character = string[j];
		fputc(character + 100, fptt);
	}
}

/******************************************************************************
 * decrypt() function description:
 * The 'decrypt()' function firstly opens and starts reading the encrypted 
 * payment information file. While reading the file, it decrypts all of 
 * the file's contents. Once the file has been fully decrypted, it's closed
 * and its contents are now accessible to everyone again - to read.   
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void decrypt() {
    char character, filename[100], unencryptedFilename[] = "unencrypted_";
	FILE *fpts, *fptt;

	/* Prompt and allow the user to input the name of the file that they 
	want to decrypt. */
	printf("Name of the file to decrypt: ");	
	scanf("%s", filename);

	/* Open and read the desired file. */
	fptt = fopen(filename, "r");

	/* If the desired file cannot be found or opened properly. */
  	if (fptt == NULL) {
		printf("FPTT File does not exist, or there's an error in opening it!");
		fclose(fptt);
		exit(9);
	}

	/* Copy the strings from the opened file, to a new file, named 
	'unencrypted_'. */
	strcat(unencryptedFilename, filename);

	/* Open and write to 'unencrypted_'. */
	fpts = fopen(unencryptedFilename, "w");

	/* If the desired file cannot be found or opened properly. */
  	if (fpts == NULL) {
		printf("File does not exist, or there's an error in opening it!");
		exit(7);
	}

	while (1) {
		character = fgetc(fptt);
		/* While the end of the desired file hasn't been reached, decrypt 
		the file, by subtracting 100 from the ASCII character index - so
		that the end product is the whole string being decrypted. When it 
		has reached the end of the file, stop decrypting. */
		if (character == EOF) {
			break;
		} else {
			character = character - 100;
			fputc(character, fpts);
		}
	}

	/* Prompt the user that the decryption of the chosen file
	was successful. */
	printf("The file %s decrypted successfully!\n\n", filename);

	/* Close both files. */
	fclose(fpts);
	fclose(fptt);
}