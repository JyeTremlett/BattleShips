/*
FILENAME:	linkedlist.c
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	

Generic linkedlist implementation. Includes declarations for
functions to:
- create a new list
- add a node to the list
- increment the list head-first
- free the list and all data
and delcarations for linkedlist and node structs
*/


#include "linkedlist.h"



/*--------------------------------------------------------------------------|

PURPOSE:
	Initialises a new list declared in the calling function.
PARAMETERS:
	Linkedlist to be initialised, and size of the data in each node.
RETURNS:
	N/A
BEHAVIOUR:
	Initialises each variable in the passed linkedlist struct.*/

void newList(linkedlist *list, int nodesize)
{
	list->listlength = 0;
	list->nodesize = nodesize;
	list->head = NULL;
	list->tail = NULL;
}



/*--------------------------------------------------------------------------|

PURPOSE:
	Adds a node to the tail of an exisiting list.
PARAMETERS:
	A linkedlist that has already been initialised  with newList(), 
	and the data to put in the new node.
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure
BEHAVIOUR:
	Mallocs the new node, then the data in the node, and copies the passed 
	data into the newly created node. Initialises head and tail pointers in 
	the linkedlist struct as appropriate.*/

int addNode(linkedlist *list, void *data)
{
	int nodesize, result;
	node *newnode;

	result = SUCCESS;
	nodesize = list->nodesize;
	newnode = malloc(sizeof(node));
	if(newnode == NULL)
	{
		result = FAILURE;
		perror("Failed to allocate new node");
	}
	newnode->data = malloc(nodesize);
	if(newnode->data == NULL)
	{
		result = FAILURE;
		perror("Failed to allocate new node data");
	}
	
	memcpy(newnode->data, data, nodesize);
	newnode->next = NULL;

	if(list->listlength == 0) 		/**if list is empty**/
	{
		list->head = newnode;
		list->tail = newnode;
	}
	else
	{
		list->tail->next = newnode; /**if list not empty**/
		list->tail = newnode;
	}

	list->listlength++;
	return result;
}



/*--------------------------------------------------------------------------|

PURPOSE:
	Pops the head of the list and makes linkedlist struct->head point to 
	head->next.
PARAMETERS:
	Linkedlist struct to be manipulated.
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure.
BEHAVIOUR:
	This function creates a temporary variable for the head, makes the 
	variable = the head, and head = head->next. Then current aka the old head
	is freed.*/

int increment(linkedlist *list)
{
	int result;
	node *currentnode;
	result = FAILURE;
	if(list->head != NULL)
	{
		currentnode = list->head;
		list->head = currentnode->next;
		list->listlength--;
		free(currentnode->data);
		free(currentnode);
		result = SUCCESS;
	}
	return result;	
}



/*--------------------------------------------------------------------------|

PURPOSE:
	Frees each node and node->data in a linkedlist.
PARAMETERS:
	Pointer to a linkedlist to be freed
RETURNS:
	N/A
BEHAVIOUR:
	Starting from the head, saves each node to a variable, increments the node
	that "head" points to, and frees the current node, until head == NULL.*/

void freeList(linkedlist *list)
{
	node *currentnode;
	currentnode = list->head;
	while(list->head != NULL)
	{
		list->head = currentnode->next;
		free(currentnode->data);
		free(currentnode);
		currentnode = list->head;
	}
}

