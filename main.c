/*
FILENAME:	main.c
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	Main file for battleships game
*/

#include "battleships.h"


/*---------------------------------------------------------------------------|

PURPOSE:
	Main function for battleships game 
PARAMETERS:
	"argc" number of arguments
	"argv" arguments provided. Should be "./battleshipsgame" followed by the 
	filename of the boardfile and missilefile
RETURNS:
	SUCCESS (1) on success or
	Failure (0) on failure
BEHAVIOUR:
	This function follows the following path:
	1. Initialises data structures for game data
	2. Display the menu and get a choice of action
	3. Loop and get consecutive menu choices until the user selects EXIT, or
		until an error occurs
		a) On choice PLAY_GAME, loops over consecutive turns until the 
			game ends as per checkdelimiters();
		b) On choice LIST_MISSILES, lists each missile loaded from the missile
			file.*/

int main(int argc, char **argv)
{

	/*respresents SUCCESS or FAILURE of main()*/
	int result;

	/*user's choice of menu option**/
	int menuchoice;

	/*struct of delimiters for ending the game*/
	delimiters *delims;

	/*
	variables storing board and missile info
	missiles 	 = linkedlist of missiles to be fired
	board 	 	 = board to be displayed and manipulated
	*/
	linkedlist *missiles;
	char	   **board;

	/*
	A hashtable implemented as an array of pointers to ship structs. This 
	works by having each array cell represent a space on the board, and using
	an algorithm I designed which maps a "location" (for example B3) to a 
	unique cell in the array. Cells that represent board locations that are
	occupied by a common ship point to the same ship struct.
	*/
	hashtable *ships;

	result = SUCCESS;

	if(argc != 3)
	{
		perror("Incorrect number of parameters");
		result = FAILURE;
	}


	/*GAME STARTS HERE*/
	menuchoice = displayMenu();
	while(menuchoice != EXIT && result == SUCCESS)
	{
		/*declaration of structs*/
		delims = 	(delimiters*)malloc(sizeof(delimiters));
		missiles = 	(linkedlist*)malloc(sizeof(linkedlist));
		ships = 	(hashtable *)malloc(sizeof(hashtable ));
		if(delims == NULL || missiles == NULL || ships == NULL)
		{
			perror("Error allocating memory for delims, missiles, or ship structs");
			result = FAILURE;
		}
		
		/**process board info file**/
		if(!processBoardFile(argv[1], ships, delims))
		{
			result = FAILURE;
		}
		
		/*process missile info file*/
		if(result == SUCCESS && !processMissileFile(argv[2], missiles, delims))
		{
			result = FAILURE;
		}
		
		/*PLAY: play game and loop over turns*/
		if(result == SUCCESS && menuchoice == PLAY_GAME)
		{
			board = (char**)malloc(sizeof(char*) * ships->boardwidth);
			createBoard(ships->boardwidth, ships->boardheight, board);

			while(checkDelimiters(delims))
			{
				simulateTurn(board, missiles, delims, ships);
			}

			/*once game has ended, free any allocated memory*/
			freeBoard(board, ships);
		}
		
		/*LIST: list missiles*/
		else if(result == SUCCESS && menuchoice == LIST_MISSILES) 
		{
			listMissiles(missiles);
		}


		freeList(missiles);
		freeTable(ships);
		free(ships);
		free(missiles);
		free(delims);

		/*get next choice of action*/
		menuchoice = displayMenu();
	}	

	/*EXIT: do nothing*/
	
	return result;
}
