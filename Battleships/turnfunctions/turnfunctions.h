/*
FILENAME:	turnfunctions.h
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	23/05/2020
PURPOSE:	Header file for turnfunctions.c and battleship gamefiles. Includes 
			function prototypes responsible for:
			- choosing a function pointer to shoot with
			- a function for each type of missile
			- checking if a location is valid to shoot
			- printing a description of what each missile does
*/


/*---------------------------------------------------------------------------|

HEADER GUARD*/
#ifndef TURNFUNCTIONS_H
#define TURNFUNCTIONS_H


/*---------------------------------------------------------------------------|

LIBRARY INCLUSIONS*/
#include "../battleships.h"


/*---------------------------------------------------------------------------|

FUNCTION PROTOTYPES
All implementation and usage in turnfunctions.c

chooses a function for what missile to shoot*/
shootFP chooseFunction(linkedlist *list);

/*function to shoot a single missile*/
void single(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation);

/*function to shoot a splash missile*/
void splash(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation);

/*function to shoot a vline missile*/
void vline(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation);

/*function to shoot a hline missile*/
void hline(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation);

/*checks the validity of a location on the board*/
int checkLocation(char **board, hashtable *ships, int x, int y);

/*prints what each missile does*/
void printMissileInfo(void);


#endif
