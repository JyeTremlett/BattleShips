/*
FILENAME:	fileprocessing.c
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	1/05/2020
PURPOSE:	

File contains functions for processing board files and missile files, as 
well as static funtions to assist with this.
*/



#include "battleships.h"


/**prototypes for functions that are in this file only**/
static int processDimensions(char *line, 	  hashtable *ships);
static int processShips(FILE *boardfile, hashtable *ships, delimiters *delims);
static int checkIfValid(ship *newship,   hashtable *ships);



/*---------------------------------------------------------------------------|

PURPOSE: 
	Checks for board file for errors saves file information
PARAMETERS:
	"boardfilename" the name of the board file to open
	"ships" the hashtable to save ships into
	"delims" delimiters to write for conditions for ending a game
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure if an error has
	occurred.
BEHAVIOUR:
	This function simply goes through and saves a line to an array. Then, it 
	is passed to processDimensions and processShips for saving to the correct
	data structures*/

int processBoardFile(char *boardfilename, hashtable *ships, 
	delimiters *delims)
{
	FILE *boardfile;
	int  result, linesize;
	char line[BUFSIZ]; /*would be smaller but specs said name could be ANY 
	number of characters*/

	linesize = sizeof(line);

	boardfile =  fopen(boardfilename, "r");
	if(boardfile == NULL || fgets(line, linesize, boardfile) == NULL)
	{
		perror("Error opening boardfile");
		result = FAILURE;
	}
		/*if getting height and width is succesful, process each line and 
		save it (done in processShip()). If processShip() is successful, 
		result = SUCCESS*/
	else if(processDimensions(line, ships) && processShips(boardfile, ships, 
		delims)) 
	{
		result = SUCCESS;
	}
	else
	{
		perror("Error 1 reading from boardfile");
		result = FAILURE;
	}

	if(ferror(boardfile))
	{
		result = FAILURE;
		perror("Error 2 reading from boardfile");
	}
	fclose(boardfile);

	return result;
}



/*---------------------------------------------------------------------------|

PURPOSE:
	checks for missiles file for errors saves file information
PARAMETERS:
	"boardfilename" the name of the board file to open
	"ships" the hashtable to save ships into
	"delims" delimiters to write for conditions for ending a game
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure if an error has
	occurred.
BEHAVIOUR:
	This function iterates throuhg a missile file, and adds missiles to a 
	generic linkedlist. If any line is invalid, returns Failure.
*/
int processMissileFile(char *missilefilename, linkedlist *missiles, delimiters
 *delims)
{
	FILE *missilefile;
	int result, linesize, nmissiles, i;
	char line[BUFSIZ];

	nmissiles = 0;
	result = SUCCESS;
	newList(missiles, sizeof(char[MAX_MISSILE_NAME_LEN])); /*needs 8 to make room for null byte*/
	linesize = sizeof(line);
	missilefile = fopen(missilefilename, "r");

	if(missilefile == NULL)
	{
		perror("Error opening missilefile");
		result = FAILURE;
	}
	else
	{
		while(fgets(line, linesize, missilefile) != NULL && result != FAILURE)
		 /**process line by line**/
		{
			for(i = 0; i < MAX_MISSILE_NAME_LEN-1; i++)
			{
				line[i] = tolower(line[i]);
			}
			if( strcmp(line, "single") || strcmp(line, "v-line") || 
				strcmp(line, "h-line") || strcmp(line, "splash"))
			{
				nmissiles++;
				result = addNode(missiles, &line);
			}
			else
			{
				result = FAILURE;
				perror("Error reading from missilefile");
			}
		}
	}
	delims->nmissiles = nmissiles;
	fclose(missilefile);
	return result;

}



/*---------------------------------------------------------------------------|

PURPOSE:
	processes the first line of the boardfile, finding the dimensions of the 
	board
PARAMETERS:
	
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure if an error has
BEHAVIOUR:
	
*/
static int processDimensions(char line[BUFSIZ], hashtable *ships)
{
	int result, width, height, nread;

	if(line != NULL)
	{	
		nread = sscanf(line, "%d, %d", &width, &height);
		if(nread == 2 && /**if successful sscanf and valid dimensions, create 
		new hashtable**/
		width  >= MIN_BOARD_SIZE && width  <= MAX_BOARD_SIZE && 
		height >= MIN_BOARD_SIZE && height <= MAX_BOARD_SIZE)
		{
			newTable(width, height, ships);
			result = SUCCESS;
		}
		else
		{
			result = FAILURE;
			perror("Incorrect number of entries read on dimensions line");
		}
	}
	else
	{
		result = FAILURE;
		perror("Failed to read dimensions line");
	}

	return result;
}



/*---------------------------------------------------------------------------|

PURPOSE:
	processes through each line in the boardfile and saves the info to the 
	ships hashtable
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
static int processShips (FILE *boardfile, hashtable *ships, delimiters *delims)
{
	ship *shiparr;
	int nships, result, linesize, nread, ylocation, length, i;
	char name[MAX_NAME_LENGTH], direction, xlocation, line[BUFSIZ];

	/*initialise delims*/
	delims->maxturns = 0;
	delims->turnstaken = 0;
	delims->nhits = 0;
	delims->maxturns = 0;


	linesize = sizeof(line);
	shiparr = malloc(sizeof(ship));
	result = SUCCESS;
	if(shiparr == NULL)
	{
		perror("Failed allocating ship array");
		result = FAILURE;
	}
	nships = 0;

	/**for each line, save ship attributes to a ship struct and put it in an array**/
	while(fgets(line, linesize, boardfile) != NULL && result != FAILURE)
	{
		nread = sscanf(line, "%c%d %c %d %s", &xlocation, &ylocation, &direction, &length, name);

		if(nread != 5)
		{
			result = FAILURE;
			perror("Invalid line in boardfile");
		}
		nships++;
		shiparr = realloc(shiparr, nships * sizeof(ship));
		if(shiparr == NULL)
		{
			result = FAILURE;
			perror("Failed realloc() in processShips");
		}
		/*unfortunately name doesn't allow spaces*/
		shiparr[nships-1] = createShip(name, direction, xlocation, ylocation, length);
		delims->nhits += length;
	}
	delims->maxturns = ships->boardwidth * ships->boardheight;

	/**now save each ship into the hashmap**/
	if(result != FAILURE)
	{
		i = 0;
		while(i < nships && result != FAILURE)
		{
			/*if checking for a valid ship fails, failure*/
			if(!checkIfValid(&shiparr[i], ships))
			{
				result = FAILURE;
				printf("failure");
			}

			/*if adding the ship fails, failure*/
			if(!addShip(ships, &shiparr[i]))
			{
				result = FAILURE;
				printf("failure");
			}

			i++;
		}
	}

	/**free shiparr**/
	
	free(shiparr);
	return result;
}




/*---------------------------------------------------------------------------|

PURPOSE:
	checks if each line in the board file is valid
PARAMETERS:
	
RETURNS:
	
BEHAVIOUR:
	
*/
static int checkIfValid(ship *newship, hashtable *ships)
{
	int result;
	char direction;
	int length, ylocation, xlocation, boardwidth, boardheight;

	direction 	= newship ->direction;
	length 		= newship ->length;
	ylocation 	= newship ->ylocation;
	xlocation 	= newship ->xlocation-64;
	boardwidth  = ships   ->boardwidth;
	boardheight = ships	  ->boardheight;

	if( direction != 'N' &&		/**check ship direction**/
		direction != 'S' &&
		direction != 'E' &&
		direction != 'W')
	{
		result = FAILURE;
		perror("Invalid ship direction");
	}
	
	else if(xlocation > boardwidth 	   ||/**check ship location**/
	xlocation < MIN_BOARD_SIZE ||
	ylocation > boardheight	   ||
	ylocation < MIN_BOARD_SIZE)
	{
		result = FAILURE;
		perror("Invalid ship dimensions");
	}

	/**check ship length**/
	/**these checks work by assuming the head is withing boundaries, which is
	ensured previously with "check ship location"**/
	else if((direction == 'N' && (ylocation + length - 1) > boardheight) ||
		(direction == 'S' && (ylocation - length) < MIN_BOARD_SIZE)	 ||
		(direction == 'E' && (xlocation - length) < MIN_BOARD_SIZE)  ||
		(direction == 'W' && (xlocation + length - 1) > boardwidth))
	{
		result = FAILURE;
		perror("Invalid ship length. Ship goes off the board");
	}

	else 	/**otherwise, SUCCESS**/
	{
		result = SUCCESS; 
	}
	return result;
}
