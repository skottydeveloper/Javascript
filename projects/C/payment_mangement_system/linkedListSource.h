#ifndef LINKEDLISTSOURCE_H
#define LINKEDLISTSOURCE_H

#include "client_information.h"
/******************************************************************************
 * List of structs used.
******************************************************************************/
struct node {
    client_t clientInformation;
    struct node *nextNode;
};

typedef struct node node_t;

/*******************************************************************************
 * The function prototypes used.
*******************************************************************************/
/* User function prototypes. */
void create();
void add();
void addIndex(int index);
void removeLast();
void removeIndex(int index);
void viewAll();
client_t getClient(int index);
int size();
void sort();

#endif