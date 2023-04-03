/*
FILENAME:	hashtable.h
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	Header file for custom hashtable of ship structs implementation. 
			Includes function prototypes  to:
			- create a new ship
			- create a new table
			- add a ship to the table
			- get a pointer to a ship in a table
			- free the table
*/


/*---------------------------------------------------------------------------|

HEADER GUARD*/
#ifndef HASHTABLE_H
#define HASHTABLE_H


/*---------------------------------------------------------------------------|

LIBRARY INCLUSIONS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*---------------------------------------------------------------------------|

ALGORITHM MACRO
maps a board location (e.g. "A4") to a position in an array of 
size width*height. Dimensions must have been converted to int and their
corresponding board location. For example, A1 becomes (0, 0) or B3 becomes 
(1, 2).
a = x dimension of position
b = y dimension of position
c = width of the board*/
#define HASH_ALG(a, b, c) (((c)*(b)) + (a))


/*---------------------------------------------------------------------------|

CONSTANTS
SUCCESS = constant for 1 aka true
FAILURE = constant for 0 aka false*/
#define MAX_NAME_LENGTH 12
#define SUCCESS 1
#define FAILURE 0


/*---------------------------------------------------------------------------|

STRUCTS
ship: holds name, direction, x and y locaiton, hits remaining, and length of
	a ship.*/
typedef struct
{
	char name[MAX_NAME_LENGTH], direction, xlocation;
	int  hitsleft, length, ylocation;
} ship;


/*hashtable: struct to hold an array of pointers to ship structs, and the 
	width and height of the board*/
typedef struct
{
	ship **list;
	int boardwidth, boardheight;
} hashtable;


/*---------------------------------------------------------------------------|

FUNCTION PROTOTYPES
full descriptions in hashtable.c

creates a new ship*/
ship createShip(char name[MAX_NAME_LENGTH], char direction, char xlocation, 
	int ylocation, int length);

/*creates a new hashtable*/
void newTable(int width, int height, hashtable *newtable);

/*adds a ship to a hashtable*/
int addShip(hashtable *table, ship *newship);

/*gets a point from the hashtable*/
ship* getShip(hashtable *table, int xlocation, int ylocation);

/*frees the hashtable*/
void freeTable(hashtable *table);


void printAllShips(hashtable *table, int boardsize);



#endif
