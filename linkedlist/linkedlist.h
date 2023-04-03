/*
FILENAME:	linkedlist.h
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	Header file for generic linkedlist implementation. Includes 
			function prototypes  to:
					- create a new list
					- add a node to the list
					- increment the list head-first
					- free the list and all data
			Declaration of linkedlist and node structs are in linkedlist.h
*/

/*---------------------------------------------------------------------------|

HEADER GUARD*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H


/*---------------------------------------------------------------------------|

LIBRARY INCLUSIONS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	


/*---------------------------------------------------------------------------|

CONSTANTS
SUCCESS = constant for 1 aka true
FAILURE = constant for 0 aka false*/
#define SUCCESS 1
#define FAILURE 0


/*---------------------------------------------------------------------------|

STRUCTS
node: Stores data for a node in the linkedlist
	- void pointer "data" makes linkedlist data generic
	- "next" points to the next node in the list*/
typedef struct node 
{
	void *data;
	struct node *next;
} node;

/*linkedlist: "Outer" struct to contain a linkedlist of nodes and some list info
	- "head" points to the head of the list
	- "tail" points to the tail of the list
	- listlength is the current number of nodes in the list
	- nodesize is the size of the datatype in node->data*/
typedef struct
{
	node *head;
	node *tail;
	int listlength;
	int nodesize;
} linkedlist;


/*---------------------------------------------------------------------------|

FUNCTION PROTOTYPES
all full descriptions and implementations in linkedlist.c

creates a new list**/
void newList(linkedlist *list, int nodesize);

/*adds a new node*/
int addNode(linkedlist *list, void *data);

/*free linkedlist*/
void freeList(linkedlist *list);

/*increment to next missile once current is fired*/
int increment(linkedlist *list);


#endif
