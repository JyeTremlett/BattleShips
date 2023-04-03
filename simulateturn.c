/*
FILENAME:	main.c
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	

File simulates each turn taken by a user. Displays the current board, number 
of missiles left not including current, and name of the current missile. 
Starts by prompting for input of a location to guess.
*/


#include "battleships.h"
#include "turnfunctions/turnfunctions.h"


/*if compiled with -D DEBUG, will show ship locations in magenta*/
#ifndef DEBUG
#define CONDITION 0
#else
#define CONDITION 1
#endif


/*displays info between turns*/
static void displayInfo(char **board, hashtable *ships, linkedlist *missiles);

/*prints the correct symbol for each board location*/
static void printLocation(char symbol, hashtable *ships, int x, int y);



/*--------------------------------------------------------------------------|

PURPOSE:
	Simulate turn is the controlling function for simulating a turn, and is
	called from main(). Calls displayInfo(), and then prompts the user for a 
	guess, which is fed to shoot(), which then fires on the relevant locations
	and ships.
PARAMETERS:
	"board" the board for display purposes
	"missiles" the linkedlist of missiles
	"delims" the structs of variables that could signify end of game
	"ships" hashtable of ships to shoot at
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure if an error has
	occurred.
BEHAVIOUR:
	This function starts by dispalying the board and all info, then prompts
	the user to guess a location. This location is checked for validity with
	checkLocation(), andif it is valid, the loop is broken and the entered 
	the next function to use is retrived by chooseFunction(). This function
	is then passed the location, and the relevant ships and locations are shot

	A user can enter !h at the prompt to be shown a list of missiles and their
	affects.*/

int simulateTurn(char **board, linkedlist *missiles, delimiters *delims, 
	hashtable *ships)
{
	int ylocation, xlocation, result, guessnotvalid;
	char cxlocation;
	shootFP shoot;

	result = SUCCESS;
	guessnotvalid = TRUE;

	displayInfo(board, ships, missiles);
	printf(".............................................................\n");

	/**while player has not guessed a valid location, keep prompting**/	
	while(guessnotvalid)
	{
		printf("\nPlease enter an x and y coordinate: ");
		scanf( " %c", &cxlocation);
		printf("\n");
		scanf(" %d", &ylocation);

		/*convert x and y locations to correct integers for board addressing*/
		cxlocation = toupper(cxlocation);
		xlocation = cxlocation-65; 
		ylocation--; 

		/*lazy but works*/
		/*if user enters !h, print missile info*/
		if(xlocation == -32)
		{
			printMissileInfo();
		}
		else
		{
			/**if location in undefined, or alread guessed, then print 
			message and guess again**/
			if(checkLocation(board, ships, xlocation, ylocation)) 
			{
				guessnotvalid = FALSE;			
			}
			else
			{
				printf("This location has already been guessed or is invalid. ");
				printf("Please enter another location\n");
			}
		}
	}

	/*once we have a valid guess, select suitable function pointer 
	and shoot the current missile*/
	shoot = chooseFunction(missiles);
	shoot(ships, delims, board, xlocation, ylocation);

	/*decrement delimiters*/
	delims->nmissiles--;
	result = increment(missiles);
	delims->turnstaken++;

	return result;
}


/*---------------------------------------------------------------------------|

PURPOSE:
	Displays the current board, the number of missiles left, and the current
	missile's name.
PARAMETERS:
	"board" array of board locations
	"ships" hashtable holding each ship
	"missiles" linkedlist holding each missile name
RETURNS:
	N/A
BEHAVIOUR:
	This function prints a visually appealing representation of the locations
	held in the char **board. Calls printLocation() for each board location so
	that the correct symbol and colour is printed. After this, number of 
	remaining missiles and current missile name is printed*/

static void displayInfo(char **board, hashtable *ships, linkedlist *missiles)
{
	int i, j, width, height;

	width  = ships->boardwidth;
	height = ships->boardheight;

	/**display board**/
	printf("\n\n    *");
	for(i = 0; i<width; i++)		
	{
		printf(" %c |", i+65);			/**print top line**/
	}
	printf("\n ****");
	for(i = 0; i<width; i++)		
	{
		printf("****");					/**print top line divider**/
	}
	printf("\n");
	for(i = 0; i<height; i++)			/**for each row**/
	{
		printf(" %d  *", i+1);				/**print y location numbers**/
		
		for (j = 0; j<width; j++)
		{
			fflush(stdout);
			printLocation(board[i][j], ships, j, i); /**print each location**/
		}
		printf("\n ");
		for (j = 0; j<width+1; j++)
		{
			printf("---+");					/**print divider between rows**/
		}
		printf("\n");
	}

	/**display missiles left**/
	printf("\nMissiles left:\t   %d\n", missiles->listlength-1);

	/**display current missile name**/
	printf("Current missile:   %s\n", (char*)missiles->head->data);

}



/*---------------------------------------------------------------------------|

PURPOSE:
	Prints the location in the correct colour
PARAMETERS:
	"symbol" symbol to print being EMPTY (X), HIT (0), or UNKNOWN (#)
	"ships" ships hashtable for checking for ship
	"x" and "x" the location currently being printed
RETURNS:
	N/A
BEHAVIOUR:
	This function checks what the symbol is and prints it in it's correct
	colour. If compiled with the DEBUG option, checks if a ship is in the 
	location and prints in magenta regardless of the symbol.*/

static void printLocation(char symbol, hashtable *ships, int x, int y)
{
	ship *foundship;
	foundship = getShip(ships, x, y);
	if(symbol == UNKNOWN)
	{			/*if compiled with debug DEBUG*/
		if(CONDITION && foundship->hitsleft != 0)
		{
			printf(" %s%c%s |", MAGENTA, symbol, RESET);
		}
		else	/*if not compiled with DEBUG*/
		{
			printf(" %s%c%s |", YELLOW, symbol, RESET);
		}
		
	}
	else if (symbol == HIT)
	{
		printf(" %s%c%s |", RED, symbol, RESET);
	}
	else if (symbol == MISS)
	{
		printf(" %s%c%s |", BLUE, symbol, RESET);
	}
}

