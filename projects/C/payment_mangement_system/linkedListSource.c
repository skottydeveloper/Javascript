/******************************************************************************
 * List of header files used.
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedListSource.h"
#include "compression.h"

/*******************************************************************************
 * The function prototypes used.
*******************************************************************************/
/* Linked list function prototypes. */
void initialiseLinkedList();
void addNewElementToEnd(node_t* headNode);
int nullNodeChecker(node_t* nodeToBeChecked);
int addElementToIndex(node_t** headNode, int index);
void viewWholeList(node_t* headNode);
node_t* findElement(node_t* headNode,int index);
client_t getDataAtIndex(node_t* headNode,int index);
client_t removeLastElement(node_t* headNode);
client_t deleteElementAtIndex(node_t** headNode, int index);
client_t getClientInfo();
int getSize(node_t* headNode);
void sortByDate(node_t** headNode);
int swapAdjacentElements(node_t** headNode, int firstIndex, int secondIndex);

/*****************************************************************************
 * List of variables used.
*****************************************************************************/
/* A pointer of the typedef struct, 'node_t'. */
node_t* headNode;

/* A double pointer of 'node_t'; 'doubleheadNode' is a pointer to 'headNode'. */
node_t** doubleheadNode = &headNode;

/* Below are the following functions to help the user manipulate the linked 
list, in order to access and modify the client information. These functions 
have been split into two sets of functions: one group being the user functions
and one group being the backend functions. The reason that the code split into
two groups is to provide additional security and more ease to the user - as
they're not required to deal with the head node of the linked list that 
they're manipulating.  

*******************************************************************************
 * User functions: These are called to access and manipulate the linked list.
******************************************************************************/

/******************************************************************************
 *                           START OF USER FUNCTIONS
******************************************************************************/

/******************************************************************************
 * create() function description: 
 * Creates a new linked list, through the initialisation of the
 * 'initialiseLinkedList()' function.
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void create() {
    initialiseLinkedList();
}

/******************************************************************************
 * add() function description: 
 * Adds an element to the end of the linked list, through the initialisation
 * of the 'addNewElementToEnd()' function, and its 'headNode' parameter. 
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void add() {
    addNewElementToEnd(headNode);
}

/******************************************************************************
 * addIndex() function description: 
 * Adds an element to the linked list at the index specified, through the 
 * initialisation of the 'addIndex()' function, with the 'doubleheadNode' 
 * pointer, and the 'index' parameter - which represents the position 
 * of the node.
 *
 * Inputs:
 * - int 'index' (an integer to represent the position of the node 
 * being added).
 *
 * Outputs:
 * - None.
******************************************************************************/
void addIndex(int index) {
    addElementToIndex(doubleheadNode, index);
}

/******************************************************************************
 * remove() function description: 
 * Removes an element from the end of the linked list, through the 
 * initialisation of the 'removeLastElement()' function, with the 'headNode'
 * pointer (which points to the node being erased).
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void removeLast() {
    removeLastElement(headNode);
}

/******************************************************************************
 * removeIndex() function description: 
 * Removes an element from the linked list at the index specified, through the
 * initialisation of the 'removeIndex()' function, with the 'doubleheadNode' 
 * pointer and the integer 'index' (which points to the node being erased).
 * 
 * Inputs:
 * - int 'index' (an integer to represent the position of the nodes).
 *
 * Outputs:
 * - None.
******************************************************************************/
void removeIndex(int index) {
    deleteElementAtIndex(doubleheadNode, index);
}

/******************************************************************************
 * viewAll() function description: 
 * Prints out all data stored in each element of the linked list, through the 
 * initialisation of the 'viewWholeList()' function, with the 'headNode'
 * pointer (which points to all of the nodes in the linked list).
 *
 * Inputs:
 * - int 'index' (an integer to represent the position of the nodes).
 *
 * Outputs:
 * - None.
******************************************************************************/
void viewAll() {
    viewWholeList(headNode);
}

/******************************************************************************
 * getClient() function description: 
 * Returns the client information stored in 'client_t', a typedef struct from 
 * the 'client_information.h' header file, through the initialisation of the 
 * 'getDataAtIndex()' function, with the 'headNode' pointer and the integer
 * 'index' (which points to the node, that the client information is being
 * retrieved from). 
 *
 * Inputs:
 * - int 'index' (an integer to represent the position of the client).
 *
 * Outputs:
 * - 'client_t' at 'index'.
******************************************************************************/
client_t getClient(int index) {
    return getDataAtIndex(headNode,index);
}

/******************************************************************************
 * size() function description:
 * Returns the size of the current linked list, through the initialisation of 
 * the 'getSize()' function, with the 'headNode' pointer (which points to the 
 * node of the linked list).
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - The size of the current list. 
******************************************************************************/
int size() {
    return getSize(headNode);
}

/******************************************************************************
 *                           END OF USER FUNCTIONS
******************************************************************************/

/******************************************************************************
 *                         START OF BACKEND FUNCTIONS
******************************************************************************/

/******************************************************************************
 * initialiseLinkedList() function description: 
 * Allocates memory for first node, points the next node to null and takes data
 * from the user to be stored.
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void initialiseLinkedList() {
    headNode = (node_t*) malloc(sizeof(node_t));
    nullNodeChecker(headNode);
    headNode->clientInformation = getClientInfo();
    headNode->nextNode = NULL;
}

/******************************************************************************
 * sort() function description: 
 * The 'sort()' function is a function that involves the user in being able 
 * to sort the currently existing payments in the list - by most recent 
 * payments made. It uses the 'sortByDate', with the 'doubleheadNode' parameter 
 * in order to do so.  
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
void sort() {
    sortByDate(doubleheadNode);
}

/******************************************************************************
 * getClientInfo() function description: 
 * Retrieves the data that the user inputs, and stores the data in the 
 * 'client' structure, via the 'client_t' typedef.
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - 'client_t' struct filled with data from user input.
******************************************************************************/
client_t getClientInfo() {
    /* Get client data via 'client_t' typedef struct. */
    client_t client;

    /* The invoice number is equal to the size of the head node, plus one. */
    client.invoice_number = getSize(headNode) + 1;

    /* Prompt user to provide their customer ID. */
     while (1) {
        int customerID;
        printf("Provide Your Information(No Spaces):\n"
        "Customer ID: ");
        int returnSuccessful = scanf("%d", &customerID);

        /* If input is a char or string. */
        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else {
            client.customerID = customerID;
            break;
        } 
    }

    /* Check if the user's input for their name is too large,
    and if so, prompt them to enter in an input that's within the 
    size range. */
    while (1) {
        char name[1000];
        int i = 0;
        printf("Name: ");
        int returnSuccessful = scanf("%s", name);

        /* Checking if name contains a number and exiting if true. */
        for (i = 0; i < strlen(name); i++) {
            if (name[i] == '2' || name[i] == '3' ||
            name[i] == '4' || name[i] == '5' || 
            name[i] == '6' || name[i] == '7' || 
            name[i] == '8' || name[i] == '9') {
                printf("Please enter a name with no numbers\n");
                returnSuccessful = 0;
                break;
            }
        }

        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else if (strlen(name) < 51) {
            char* unCompressedDataP = name;
            char* CompressedDataP = compress(unCompressedDataP);
            strcpy(client.name, CompressedDataP);
            printf("Name has been compressed and stored," 
            "compressed string is %s\n", CompressedDataP);
            break;
        } else {
            printf("Input is too large. Enter again.\n");
        } 
    }
    
    /* Check if the user's input for their business name is too large,
    and if so, prompt them to enter in an input that's within the 
    size range. */
    while (1) {
        char business_name[1000];
        int i = 0;

        /* Prompt user to input their business name. */
        printf("Business name: ");

        int returnSuccessful = scanf("%s", business_name);

        for (i = 0; i < strlen(business_name); i++) {
            if (business_name[i] == '2' || business_name[i] == '3' ||
            business_name[i] == '4' || business_name[i] == '5' || 
            business_name[i] == '6' || business_name[i] == '7' || 
            business_name[i] == '8' || business_name[i] == '9') {
                printf("Please enter a name with no numbers\n");
                returnSuccessful = 0;
                break;
            }
        }

        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else if (strlen(business_name) < 101) {
            char* unCompressedDataP = business_name;
            char* CompressedDataP = compress(unCompressedDataP);
            printf("Business Name has been compressed and stored," 
            "compressed string is %s\n", CompressedDataP);
            strcpy(client.business_name, CompressedDataP);
            break;
        } else {
            printf("Input is too large. Enter again.\n");
        }
    }
    
    /* Prompt user to input the amount paid. */
    while (1) {
        int amount_paid;
        printf("Amount to pay: ");
        int returnSuccessful = scanf("%d", &amount_paid);

        /* If input is a char or string. */
        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else {
            client.amount_paid = amount_paid;
            break;
        } 
    }
    
    /* Prompt user to input their bank account identifier. */
    printf("Bank Account Identifier: ");
    scanf("%s", client.bank_account);
    
    /* Check if the user's input for the day of payment is invalid,
    and if so, prompt them to enter in an input that's within the 
    accepted range. */
    while (1) {
        int day;
        printf("Date\nDay: ");
        int returnSuccessful = scanf("%d", &day);

        /* If input is a char or string. */
        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else if (day > 31 || day < 1) {
            printf("Invalid day. Enter again.\n");
        } else {
            client.date_of_payment.day = day;
            break;
        } 
    }

    /* Check if the user's input for the month of payment is invalid,
    and if so, prompt them to enter in an input that's within the 
    accepted range. */
    while (1) {
        int month;
        printf("Month: ");
        int returnSuccessful = scanf("%d", &month);

        /* If input is a char or string. */
        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else if (month > 12 || month < 1) {
            printf("Invalid month. Enter again.\n");
        } else {
            client.date_of_payment.month = month;
            break;
        } 
    }

    /* Check if the user's input for the year of payment is invalid,
    and if so, prompt them to enter in an input that's within the 
    accepted range. */
    while (1) {
        int year;
        printf("Year: "); 
        int returnSuccessful = scanf("%d", &year);

        /* If input is a char or string. */
        if (returnSuccessful < 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        } else if (year > 2021 || year < 1980) {
            printf("Invalid year. Enter again.\n");  
        } else {
            client.date_of_payment.year = year;
            break;
        }
    }

    return client;
}

/******************************************************************************
 * addNewElementToEnd() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and then adds data to a new node at the end of the current list.
 *
 * Inputs:
 * - 'node_t' pointer to the 'headNode'.
 *
 * Outputs:
 * - None.
******************************************************************************/
void addNewElementToEnd(node_t* headNode) {
    node_t* iteratorNode;
    iteratorNode = headNode;
    
    while (nullNodeChecker(iteratorNode->nextNode) == 0) {
        iteratorNode = iteratorNode->nextNode;
    }

    iteratorNode->nextNode = (node_t*) malloc(sizeof(node_t));
    iteratorNode->nextNode->clientInformation = getClientInfo();
    iteratorNode -> nextNode -> nextNode = NULL;
}

/******************************************************************************
 * removeLastElement() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and then removes data from the node at the end of the current list.
 *
 * Inputs:
 * - 'node_t' pointer to the headNode.
 *
 * Outputs:
 * - the 'client_t' structure removed from the list.
******************************************************************************/
client_t removeLastElement(node_t* headNode) {
    node_t* iteratorNode;
    iteratorNode = headNode;
    client_t lastClientInfo;

    if (nullNodeChecker(headNode->nextNode) == 1) {
        lastClientInfo = headNode->clientInformation;
        free(headNode);
        return lastClientInfo;
    }

    while (nullNodeChecker(iteratorNode->nextNode->nextNode) == 0) {
        iteratorNode = iteratorNode->nextNode;
    }

    lastClientInfo = iteratorNode->nextNode->clientInformation;
    free(iteratorNode->nextNode);
    iteratorNode->nextNode = NULL;
    return lastClientInfo;  
}

/******************************************************************************
 * nullNodeChecker() function description: 
 * This function checks if the 'node_t*' given to it returns a null value.
 *
 * Inputs:
 * - A 'node_t' pointer. 
 *
 * Outputs:
 * - Returns 1 if the node to checked is null, 0 if not null.
******************************************************************************/
int nullNodeChecker(node_t* nodeToBeChecked) {
    if (nodeToBeChecked == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/******************************************************************************
 * viewWholeList() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and displays all the client information to the user - from all nodes,
 * via the 'client_t typedef', of the 'client' struct. 
 *
 * Inputs:
 * - 'node_t' pointer to the 'headNode'.
 *
 * Outputs:
 * - None.
******************************************************************************/
void viewWholeList(node_t* headNode) { 
    node_t* iteratorNode;
    iteratorNode = headNode;

    while (nullNodeChecker(iteratorNode) == 0) {
        printf("Invoice number: %d\n",iteratorNode->
        clientInformation.invoice_number);
	    
        printf("Customer ID: %d\n",iteratorNode->clientInformation.customerID);

	    printf("Name: %s\n",iteratorNode->clientInformation.name);
	    
        printf("Business name: %s\n",iteratorNode->
        clientInformation.business_name);

	    printf("Bank account number: %s\n",iteratorNode->
        clientInformation.bank_account);

	    printf("Amount paid: %d\n",iteratorNode->clientInformation.amount_paid);

	    printf("Date of payment: %d-%d-%d\n\n",iteratorNode->
        clientInformation.date_of_payment.day,iteratorNode->
        clientInformation.date_of_payment.month,
        iteratorNode->clientInformation.date_of_payment.year);
        
        iteratorNode = iteratorNode->nextNode;
    }
}

/******************************************************************************
 * findElement() function description: 
 * Creates an iterator that jumps through the linked list, incrementing a 
 * counter each time it does so, and then finds and displays the data from 
 * the specified node in the current list when the counter equals the index
 * specified.
 * 
 *
 * Inputs:
 * - 'node_t' pointer to the 'headNode'.
 * - Index of the node to be found.
 * 
 * Outputs:
 * - The node at the index specified.
******************************************************************************/
node_t* findElement(node_t* headNode, int index) {
    int indexCount = 0;
    node_t* iteratorNode;
    iteratorNode = headNode;

    while (indexCount != index) {
        indexCount++;
        iteratorNode = iteratorNode->nextNode;
    }

    return iteratorNode;
}

/******************************************************************************
 * getSize() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and then displays the size of the current list.
 *
 * Inputs:
 * - 'node_t' pointer to the 'headNode'.
 *
 * Outputs:
 * - An int which is the size of the current linked list.
******************************************************************************/
int getSize(node_t* headNode) {
    if (headNode == NULL) {
        return -1;
    }

    int indexCount = 0;
    node_t* iteratorNode;
    iteratorNode = headNode;

    while (iteratorNode->nextNode != NULL) {
        indexCount++;
        iteratorNode = iteratorNode->nextNode;
    }

    return indexCount;
}

/******************************************************************************
 * getDataAtIndex() function description: 
 * A node pointer is used to go through the linked list until it finds the
 * the chosen node, at the chosen index of the current linked list. 
 * All of the client's information will then be displayed to the user from the
 * chosen node, via the 'clientInformation' variable, of the 'client_t' 
 * typedef struct. 
 *
 * Inputs:
 * - 'node_t' pointer to the 'headNode'.
 * - Index of 'client_t' struct to be retrieved.
 *
 * Outputs:
 * - A 'client_t' structure from the node at the specified index.
******************************************************************************/
client_t getDataAtIndex(node_t* headNode, int index) {
    node_t* nodeToBePrinted = findElement(headNode, index);
    return (nodeToBePrinted->clientInformation);
}

/******************************************************************************
 * deleteFirstElement() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and then removes data from the first node of the current linked list.
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 * 
 * Outputs:
 * - 'client_t' structure contained by the node deleted.
******************************************************************************/
client_t deleteFirstElement(node_t** headNode) {
    client_t lastClientInfo;
    node_t* iteratorNode;
    lastClientInfo = (*headNode)->clientInformation;
    iteratorNode = (*headNode)->nextNode;
    free(*headNode);
    *headNode = iteratorNode;
    return lastClientInfo;
}

/******************************************************************************
 * deleteElementAtIndex() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and removes data from the chosen node, at the chosen index of the 
 * current linked list. 
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 * - Index of node to be deleted.
 *
 * Outputs:
 * - 'client_t' structure contained by the node deleted.
******************************************************************************/
client_t deleteElementAtIndex(node_t** headNode, int index) {
    int indexCount = 0;
    client_t lastClientInfo;
    node_t* iteratorNode;
    iteratorNode = *headNode;
    
    if (index > getSize(iteratorNode)) {
        printf("The index entered is greater than the "
        "size of the linked list. Exiting...\n");
        return lastClientInfo;
    }

    if (index == 0) {
        lastClientInfo = deleteFirstElement(headNode);
        return lastClientInfo;
    }

    while (indexCount != index - 1) {
        indexCount++;
        iteratorNode = iteratorNode->nextNode;
    }
    
    lastClientInfo = iteratorNode->nextNode->clientInformation;
    node_t* temp = iteratorNode->nextNode;
    iteratorNode->nextNode = iteratorNode->nextNode->nextNode;
    free(temp);
    
    return lastClientInfo;
}

/******************************************************************************
 * addNewHead() function description: 
 * Creates a new head node (first node), and adds it to the start of the
 * current linked list.
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 *
 * Outputs:
 * - None.
******************************************************************************/
void addNewHead(node_t** headNode) {
    node_t* newNode;
    newNode = (node_t *) malloc(sizeof(node_t));
    newNode->clientInformation = getClientInfo();
    newNode->nextNode = (*headNode);
    (*headNode) = newNode;
}

/******************************************************************************
 * addElementAtIndex() function description: 
 * Creates an iterator that jumps through the linked list until 'nextNode' is
 * null, and adds data for a new node to the current linked list - at the
 * chosen index of the linked list. 
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 *
 * Outputs:
 * - 'int' signaling if the addition of the node succeeded or failed.
******************************************************************************/
int addElementToIndex(node_t** headNode, int index) {
    int indexCount = 0;
    node_t* iteratorNode;
    iteratorNode = *headNode;
    node_t* newNode;

    if (index == 0) {
        addNewHead(headNode);
        return 0;
    }

    if (index > getSize(iteratorNode)) {
        printf("The index entered is greater than the "
        "size of the linked list. Exiting...\n");
        return 1;
    }

    while (indexCount != index - 1) {
        indexCount++;
        iteratorNode = iteratorNode->nextNode;
    }

    newNode = (node_t *) malloc(sizeof(node_t));
    newNode->clientInformation = getClientInfo();
    node_t* temp = iteratorNode->nextNode->nextNode;
    iteratorNode->nextNode = newNode;
    newNode->nextNode = temp;

    return 0;
}

/******************************************************************************
 * swapAdjacentElements() function description: 
 * The 'swapAdjacentElements()' function involves the user in being able to 
 * swap the positions of currently existing payments in the list - that are 
 * adjacent to each other, in position. e.g. swapping the places of payment in 
 * position two, with the place of the payment in position three.  
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 *
 * Outputs:
 * - 'int' signaling if the addition of the node succeeded or failed.
******************************************************************************/
int swapAdjacentElements(node_t** headNode, int firstIndex, int secondIndex) {
    node_t* initialNode = malloc(sizeof(node_t));
    
    if (secondIndex < firstIndex) {
        printf("Wrong order of parameters for swap\n");
        return 1;
    }
    
    node_t* firstNode = findElement(*headNode, firstIndex);
    node_t* secondNode = findElement(*headNode, secondIndex);

    firstNode->nextNode = secondNode->nextNode;
    secondNode->nextNode = firstNode;

    if (firstIndex == 0) {
        *headNode = secondNode;
        return 0;
    } else {
        initialNode = findElement(*headNode, firstIndex - 1);
        initialNode->nextNode = secondNode;
        return 0;
    }
}
 
/******************************************************************************
 * sortByDate() function description: 
 * The 'sortByDate()' function is a user interface function that involves 
 * the user in being able to sort the currently existing payments in the 
 * list - by the date of payment. By doing so, it provides readability for the
 * user. The process of sorting by date involves using the process of bubble 
 * sorting, which involves continuously swapping the elements of each payment,
 * until they're all properly sorted, in the order of the most recent payment.   
 *
 * Inputs:
 * - 'node_t' double pointer to the 'headNode'.
 *
 * Outputs:
 * - None.
******************************************************************************/
void sortByDate(node_t** headNode) {
    int i, j;

    /* The date of all the payments (year, month, date) is converted into the
    format of 'DDMMYYYY'. The for loops and if statements work as a bubble 
    sort to sort each of these payments, until they're all listed and sorted
    by most recent payments made. */
    for (i = 0; i < getSize(*headNode); i++) {
        for (j = 0; j < getSize(*headNode) - i; j++) {
            if ((getDataAtIndex(*headNode, j + 1).date_of_payment.year * 10000 
            + getDataAtIndex(*headNode, j + 1).date_of_payment.month * 100 + 
            getDataAtIndex(*headNode, j + 1).date_of_payment.day) 
            > (getDataAtIndex(*headNode, j).date_of_payment.year * 10000 + 
            getDataAtIndex(*headNode, j).date_of_payment.month * 100 + 
            getDataAtIndex(*headNode, j).date_of_payment.day)) {
                swapAdjacentElements(headNode, j, j + 1);
            }
        }
    }

    /* Print out the result of the bubble sort, i.e. the newly sorted 
    list of payments. */
    printf("Sorted list of payments by most recent purchase.\n");
    viewWholeList(*headNode);
}