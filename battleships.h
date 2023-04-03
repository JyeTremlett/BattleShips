/*
FILENAME:	battleships.h
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	25/05/2020
PURPOSE:	Header file for main.c and battleship gamefiles. Includes function
			prototypes responsible for:
			- getting board and missile file info
			- display a menu
			- create a board for display
			- list the missiles available
			- check if the game has ended yet
			- simulate a turn
			- display the board on stdout
			- clean up any allocated memory
			- create board and missile files
*/


/*---------------------------------------------------------------------------|

HEADER GUARD*/
#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H


/*---------------------------------------------------------------------------|

LIBRARY INCLUSIONS*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hashtable/hashtable.h"
#include "linkedlist/linkedlist.h"


/*---------------------------------------------------------------------------|
STRUCTS
delimiters for ending the game
nmissiles  = number of missiles remaining
nhits	   = number of locations to hit remaining
turnstaken = number of turns taken
maxturns   = maximum number of turns possible*/
typedef struct
{
	int nmissiles, nhits, turnstaken, maxturns;
} delimiters;

typedef void (*shootFP)(hashtable*, delimiters*, char**, int, int);


/*---------------------------------------------------------------------------|

CONSTANTS*/
#define MAX_BOARD_SIZE 12
#define MIN_BOARD_SIZE 1
#define MIN_NAME_LEN   1

#define PLAY_GAME 	   		1
#define LIST_MISSILES  		2
#define EXIT		   		0

#define UNKNOWN '#'
#define MISS 	'X'
#define HIT   	'0'

#define SUCCESS		1
#define FAILURE		0

#define TRUE 		1
#define FALSE		0	


/*---------------------------------------------------------------------------|

CONDITIONAL COMPILATION
when compiled with -D MONO colours are removed from display*/
#ifndef MONO
#define RED 	"\033[0;31m"
#define BLUE	"\033[1;34m"
#define RESET	"\033[0m"
#define YELLOW	"\033[0;33m"
#define MAGENTA	"\033[1;35m"
#else
#define RED 	"\033[0m"
#define BLUE	"\033[0m"
#define RESET	"\033[0m"
#define YELLOW	"\033[0m"
#define MAGENTA	"\033[0m"
#endif


/*---------------------------------------------------------------------------|

FUNCTION PROTOTYPES*/

/*checks for board file for errors saves file information
- implemented in fileprocessing.c
- used in main.c*/
int  processBoardFile(char *boardfilename, hashtable *ships,  
	delimiters *delims);

/*checks for missiles file for errors saves file information
- implemented in fileprocessing.c
- used in main.c*/
int  processMissileFile(char *missilefilename, linkedlist *missiles, 
	delimiters *delims);

/*prints menu and takes in a choice of action from the uer. Prints a message 
confirming the choice
- implemented in displaymenu.c
- used in main.c*/
int  displayMenu();

/*creates a board for display of specified dimensions
- implemented in turnsupports.c
- used in main.c*/
void createBoard(int width, int height, char **board);

/*lists missiles available
- implemented in turnsupports.c
- used in main.c*/
void listMissiles(linkedlist *missiles);

/*checks delimiters to ensure game has not ended
- implemented in turnsupports.c
- used in main.c*/
int  checkDelimiters(delimiters *delims);

/*simulates one turn
- implemented in simulateturn.c
- used in main.c*/
int  simulateTurn(char **board, linkedlist *missiles, delimiters *delims, 
	hashtable *ships);

/*cleans up memory
- implemented in turnsupports.c
- used in main.c*/
void freeBoard(char **board, hashtable *ships);



#endif
