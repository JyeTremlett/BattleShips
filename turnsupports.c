/*
FILENAME:	turnsupports.c
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



/*---------------------------------------------------------------------------|

PURPOSE:
	
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
void createBoard(int width, int height, char **board)
{
	int i, j;

	for(i = 0; i < height; i++)
	{
		board[i] = (char*)malloc(width * sizeof(char));
		for(j = 0; j<width; j++)
		{
			board[i][j] = UNKNOWN;
		}
	}
}



/*---------------------------------------------------------------------------|

PURPOSE:
	
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
int checkDelimiters(delimiters *delims)
{
	int result;
	char* separator;
	result = SUCCESS;
	
	separator = "\n**************************************\n";

	if(delims->nhits <= 0 && result == SUCCESS)
	{
		printf("%s", separator);
		printf("ALL SHIPS DESTROYED. GAME ENDING");
		printf("%s", separator);
		result = FAILURE;
	}
	if(delims->nmissiles <= 0 && result == SUCCESS)
	{
		printf("%s", separator);
		printf("GAME ENDING. RAN OUT OF MISSILES");
		printf("%s", separator);
		result = FAILURE;
	}
	if(delims->turnstaken >= delims->maxturns && result == SUCCESS)
	{
		printf("%s", separator);
		printf("ALL POSSIBLE GUESSES MADE. GAME ENDING");
		printf("%s", separator);
		result = FAILURE;
	}
	return result;
}



/*---------------------------------------------------------------------------|

PURPOSE:
	
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
void listMissiles(linkedlist *missiles)
{
	node *currentmissile;
	currentmissile = missiles->head;
	printf("\n%s", (char*)currentmissile->data);
	while(currentmissile->next != NULL)
	{
		currentmissile = currentmissile->next;
		printf("%s", (char*)currentmissile->data);
	}
	printf("\n");
}



/*---------------------------------------------------------------------------|

PURPOSE:
	
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
void freeBoard(char **board, hashtable *ships)
{
	int i;
	for(i = 0; i < ships->boardwidth; i++)
	{
		free(board[i]);
	}
	free(board);
}




/*---------------------------------------------------------------------------|

PURPOSE:
	Displays a menu for the player to choose options from. If an invalid choice 
is entered, loops and asks for new inputs until the player makes valid input
	1 starts a new game
	2 lists missiles
	0 exits
returns choice to main() for execution of each option
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
int displayMenu(void)
{
	int selection;
	char input[3];
	char* separator;

	/*display menu options*/
	printf("\nMENU:\nplease select one of the following "
		"by entering a value\n");
	printf("Enter 1 to play the game\n"
		"Enter 2 to list all missiles\n"
		"Enter 0 to exit\n ");

	/*while no valid input has been given, prompt for input*/
	do
	{
		fgets(input, sizeof(input), stdin);
	} 
	while(!strcmp(input, "0\n") && !strcmp(input, "1\n") && !strcmp(input, "2\n"));
	
	/*convert selection to integer*/
	selection = input[0] - '0';

	/*take appropriate action for given entry*/
	separator = "\n**************************************\n";
	if(selection == EXIT)
	{
		printf("%s", separator);
		printf("\tGAME QUIT. EXITING");
		printf("%s", separator);
	}
	else if(selection == PLAY_GAME)
	{
		printf("%s", separator);
		printf("\tNEW GAME");
		printf("%s", separator);
	}
	else if(selection == LIST_MISSILES)
	{
		printf("%s", separator);
		printf("\tLISTING MISSILES");
		printf("%s", separator);
	}
	else
	{
		printf("\nINVALID INPUT\nPlease enter either 0, 1, or 2, in order to select from the menu\n\n");
	}
	return selection;
}

