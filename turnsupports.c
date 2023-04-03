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
	result = SUCCESS;

	if(delims->nhits <= 0 && result == SUCCESS)
	{
		printf("\n********************************\n");
		printf("ALL SHIPS DESTROYED. GAME ENDING\n");
		printf("********************************\n");
		result = FAILURE;
	}
	if(delims->nmissiles <= 0 && result == SUCCESS)
	{
		printf("\n********************************\n");
		printf("GAME ENDING. RAN OUT OF MISSILES\n");
		printf("********************************\n");
		result = FAILURE;
	}
	if(delims->turnstaken >= delims->maxturns && result == SUCCESS)
	{
		printf("\n**************************************\n");
		printf("ALL POSSIBLE GUESSES MADE. GAME ENDING\n");
		printf("**************************************\n");
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
	printf("\n\t%s", (char*)currentmissile->data);
	do
	{
		currentmissile = currentmissile->next;
		printf("\t%s", (char*)currentmissile->data);

	} while(currentmissile->next != NULL);
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
	int input;
	{
		input = 5;
		printf("\t\tMENU:\nplease select one of the following "
			"by entering a value\n");
		printf("Enter 1 to play the game\n"
			"Enter 2 to list all missiles\n"
			"Enter 0 to exit\n ");

		/*while no valid input has been givien...*/
		while(input != 0 && input != 1 && input != 2 && input != 3 && input != 4)
		{
			scanf(" %d", &input);
			if(input < 0 || input > 4)
			{
				printf("\nINVALID INPUT\n");
			}
		}
	}

	if(input == EXIT)
	{
		printf("\n********************************\n");
		printf("\tGAME QUIT. EXITING\n");
		printf("********************************\n");
	}

	if(input == PLAY_GAME)
	{
		printf("\n********************************\n");
		printf("\tNEW GAME\n");
		printf("********************************\n");
	}

	if(input == LIST_MISSILES)
	{
		printf("\n********************************\n");
		printf("\tLISTING MISSILES\n");
		printf("********************************\n");
	}


	return input;
}

