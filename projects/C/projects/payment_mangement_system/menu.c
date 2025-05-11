/******************************************************************************
 * List of header files used.
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedListSource.h"
#include "encryption.h"
#include "compression.h"

/******************************************************************************
 * List of structs used.
******************************************************************************/
struct employerLogin {
    char username[50], password[50]; 
};

typedef struct employerLogin employerLogin_t;

/******************************************************************************
 * List of preprocessing directives used.
******************************************************************************/
#define MAX_EMPLOYER_NUMBER 10

/******************************************************************************
 * Function definitions.
******************************************************************************/
void clientMenu(void);
void employerMenu(void);
int employerLogin(int employerNumber, employerLogin_t employers[]);
void showCurrentCustomers(void);

/******************************************************************************
 * List of variables used.
******************************************************************************/
int debugActivated;

/******************************************************************************
* The main() function.                               
******************************************************************************/
int main(int argc, char* argv[]) { 
    int employerCount = 0;
    int choice;
    int isBadInput = 1;

    /* User is first prompted to provide an index of an existing command
    line argument. */
    if (argc == 1) {
        printf("Please supply a Command Line Argument:" 
        "\n-d = Debug mode, -r = User Mode\n");
        exit(1);
    }
    
    /* Checks for if the user is in debug mode, via multiple command 
    arguments. */ 
    if (strcmp(argv[1], "-d") == 0) {
        printf("Debug mode activated.\n");
        debugActivated = 1;
    } else if (strcmp(argv[1], "-r") == 0) {
        debugActivated = 0;
    } else {
        printf("Unrecognised Command Line Argument\n");
        exit(1);
    }

    employerLogin_t employerLogins[MAX_EMPLOYER_NUMBER];
    
    /* Allocate "johnsmith" as a valid username for the system. */
    strcpy(employerLogins[0].username, "johnsmith");

    /* Debug mode prompt. */
    if (debugActivated == 1) {
        printf("Added %s as a valid manager username.\n", 
        employerLogins[0].username);
    }
    
    /* Allocate "123" as a valid password for the system. */
    strcpy(employerLogins[0].password, "123");

    /* Debug mode prompt. */
    if (debugActivated == 1) {
        printf("Added %s as a valid manager password.\n", 
        employerLogins[0].password);
    }

    /* Allocate "janesmith" as a valid username for the system. */
    strcpy(employerLogins[1].username, "janesmith");

    /* Debug mode prompt. */
    if (debugActivated == 1) {
        printf("Added %s as a valid manager username.\n", 
        employerLogins[1].username);
    }

    /* Allocate "321" as a valid password for the system. */
    strcpy(employerLogins[1].password, "321");

    /* Debug mode prompt. */
    if (debugActivated == 1) {
        printf("Added %s as a valid manager password.", 
        employerLogins[1].password);
    }

    employerCount = 2;
    
    while (choice != 3) {
        /* Prompt and allow user to input their choice. */
        printf("\n\t~~Payroll Management System~~\t\n\n"
        "Choose your login:"
        "\n1: Client"
        "\n2: Manager\n");

        printf("3: Exit System\n"
        "Your Choice: ");

        isBadInput = scanf("%d", &choice);

        /* If the choice is invalid, close the program. */
        if (isBadInput < 1) {
            printf("Bad Input, Please Enter a Number.\n");
            printf("Exiting Program...\n");
            exit(1);
            break;
        }

        switch (choice) {
            case 1: 
                /* Open the menu for the client. */
                clientMenu();

                if (debugActivated == 1) {
                    printf("Entered the client menu.");
                }
                break;
            case 2: 
                /* Employer logs in here, password protected as
                extra security for data. */
                if (employerLogin(employerCount, employerLogins) == 1) {   
                    employerMenu();

                    /* Debug mode prompt. */
                    if (debugActivated == 1) {
                        printf("Entered the employer's menu.");
                    }
                } else {
                    printf("Invalid login details, please try again.\n");
                }  
                break;
            case 3:
                /* Exit the system. */
                printf("Exiting system. Goodbye...\n");
                break;
            default:
                break;
        }

        /* Exit the system. */
        if (choice == 3) {
            break;
        }
       
        /* If the choice isn't any of the three choices, prompt the user 
        and close the program. */
        if (choice != 1 && choice != 2 && choice != 3) {
            printf("Invalid entry. Exiting program...\n");
            break;
        }
    }

    return 0;
}

/******************************************************************************
 * clientMenu() function description: 
 * The 'clientMenu()' function involves displaying a menu for the client, when
 * they select the option to display it, from the main menu of the program.
 * Here, the client can make payments and close the menu - when they're 
 * done doing so. 
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void clientMenu() {
    int choice;
    int isBadInput = 1;

    while (choice != 2) {
        /* Prompt and allow user to input their choice. */
        printf("Choose an Option"
        "\n1: Make a Payment"
        "\n2: Exit Client Menu\n"
        "Your Choice: ");
        isBadInput = scanf("%d", &choice);

        /* If the choice is invalid, close the program. */
        if (isBadInput < 1) {
            printf("Bad Input, Please Enter a Number.\n");
            printf("Exiting Program...\n");
            exit(1);
            break;
        }
        
        switch (choice) {
            case 1:
                /* If there's a list of payments, allow the user to add to the
                existing list, else allow the user to create a new list. */
                if (size() == -1) {
                    create(debugActivated);

                    /* Debug mode prompt. */
                    if (debugActivated == 1) {
                        printf("Creating a new list...");
                    }
                } else {
                    add();

                    /* Debug mode prompt. */
                    if (debugActivated == 1) {
                        printf("Adding to new list...");
                    }
                }
                break;
            case 2: 
                /* Exit the menu. */
                printf("Exiting menu...\n");
                break;
            default:
                break;
        }

        /* Exit the menu. */
        if (choice == 2) {
            break;
        }
       
        /* If the choice isn't any of the two choices, prompt the user 
        to input again. */
        if (choice != 1 && choice != 2 && choice != 0) {
            printf("Invalid entry. Please retry...\n");
            choice = 0;
            break;  
        }
    }
}

/******************************************************************************
 * employerMenu() function description: 
 * The 'employerMenu()' function involves displaying a menu for the employer, 
 * when they select the option to display it, from the main menu of the 
 * program. Here, the employer can decrypt a file, encrypt all data, add to an
 * existing document, compress the document, encrypt a specific client's data,
 * sort records and exit the employer menu - when they're finished with doing
 * what needs to be done. 
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void employerMenu() {
    int choice;
    int isBadInput = 1;
    
    while (choice != 5) {
        /* Prompt and allow user to input their choice. */
        printf("Choose an Option"
        "\n1: Decrypt a File"
        "\n2: Encrypt All Data, Add to Document and Compress"
        "\n3: Encrypt a Specific Clients Data, Add to Document and Compress "
        "\n4: Sort Records"
        "\n5: Exit Employer Menu\n"
        "Your Choice: ");
        isBadInput = scanf("%d", &choice);

        /* If the choice is invalid, close the program. */
        if (isBadInput < 1) {
            printf("Bad Input, Please Enter a Number.\n");
            printf("Exiting Program...\n");
            exit(1);
        }
        
        switch (choice) {
            case 1:
                /* Allow the user to decrypt a file. */
                decrypt(debugActivated);

                /* Debug mode prompt. */
                if (debugActivated == 1) {
                    printf("Performing decrypt function...");
                }
                break;
            case 2:
                /* Allow the user to encrypt all data, and compress it. */
                encryptAll(debugActivated);

                /* Debug mode prompt. */
                if (debugActivated == 1) {
                    printf("Performing encrypt all function...");
                }
                break;
            case 3:
                /* Allow the user to select a current customer and encrypt 
                their data. */
                showCurrentCustomers();
                encryptSpecific(debugActivated);

                /* Debug mode prompt. */
                if (debugActivated == 1) {
                    printf("Showing list of customers...\n"
                    "Performing encrypt specific function...");
                }
                break;
            case 4:
                /* Allow the user to sort their payment information, by 
                most recent purchases made. */
                sort();
                break;
            case 5:
                break;
            default:
                break;
        }

        /* Exit the menu. */
        if (choice == 5) {
            break;
        }
       
        /* If the choice isn't any of the five choices, prompt the user 
        to input again. */
        if (choice != 1 && choice != 2 && choice != 3 && 
        choice != 4 && choice != 0) {
            printf("Invalid entry, please retry...\n");
            choice = 0;
        }
    }
}

/******************************************************************************
 * showCurrentCustomers() function description: 
 * The 'showCurrentCustomers()' function involves displaying a list of all the 
 * current customers for the employer, when they select the option to do so, 
 * from the employer menu of the program.
 *
 * Inputs:
 * - 'business_name' from the client struct.
 * - 'date_of_payment' (day, month, year) from the client struct.
 *
 * Outputs:
 * - None.
******************************************************************************/
void showCurrentCustomers(void) {
    int i;

    /* Debug mode prompt. */
    if (debugActivated == 1) {
        printf("Showing list of current customers...");
    }

    printf("The following clients have made a payment recently:\n\n");
    
    for (i = 0; i < size() + 1; i++) {
        /* Get list of clients that have made a recent payment. */
        client_t client = getClient(i);
        printf("Business Name: %s\nDate: %d-%d-%d\n\n", client.business_name,
        client.date_of_payment.day, client.date_of_payment.month, 
        client.date_of_payment.year);
    }
}

/******************************************************************************
 * employerLogin() function description: 
 * For the employer to access the employer menu, they must first login. 
 * The 'employerLogin()' involves prompting the employer to login, using their
 * username and password. If the username and password is valid, they're
 * allowed to access the employer menu.  
 *
 * Inputs:
 * - 'attemptedUsername'.
 * - 'attemptedPassword'.
 *
 * Outputs:
 * - None.
******************************************************************************/
int employerLogin(int employerCount, employerLogin_t employers[]) {
    int foundLogin = 0, i = 0;
    char attemptedUsername[50], attemptedPassword[50];
    
    /* Prompt and allow employer to input their username. */
    printf("Username: ");
    scanf("%s", attemptedUsername);
    
    /* Prompt and allow employer to input their password. */
    printf("\nPassword: ");
    scanf("%s", attemptedPassword);

    for (i = 0; i < employerCount; i++) {
        /* If the employer's username and password inputs are correct, 
        accept the inputs as valid, and allow them further access to the
        system. */
        char *usernameP = (employers[i].username);
        char *passwordP = (employers[i].password);
        
        if (strcmp(attemptedUsername, usernameP) == 0 
        && strcmp(attemptedPassword, passwordP) == 0) {
            foundLogin = 1;
        }
    }

    return foundLogin;
}