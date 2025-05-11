#ifndef CLIENT_INFORMATION_H
#define CLIENT_INFORMATION_H

/******************************************************************************
 * 'date' struct description: 
 * Consists of the 'day', 'month' and 'year' variables - each in the form 
 * of an integer. This struct is called, when the date of a payment 
 * (or several payments) is required to be displayed, via its typedef 
 * struct, 'date_t' - in the 'client' struct (which is below).  
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
struct date {
    int day, month, year;
};

typedef struct date date_t;

/******************************************************************************
 * 'client' struct description: 
 * Consists of the 'invoice_number', 'customerID', 'name', 'date_of_payment',
 * 'business_name', 'bank_account' and 'amount_paid' variables - each in the
 * form of either an integer or a char of 50-100 characters. This struct is
 * called, when the clients' information is required to be retrieved and 
 * displayed, via its typedef struct, 'client_t' - in the 'getClientInfo()'
 * function.   
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
struct client {
    int invoice_number;
    int customerID;
	char name[50];
	date_t date_of_payment;
    char business_name[100];
	char bank_account[100];
    int amount_paid;
};

typedef struct client client_t;

#endif