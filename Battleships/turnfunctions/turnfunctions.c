/*
FILENAME:	turnfunctions.c
AUTHOR:		Jye Tremlett
STUDENT #:	2021798s7
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	

These functions assist simulateTurn(); which is called from main. These
functions are used for the "shooting" part of a turn, whereby a user fires
and a missile affects it's specified area. 

Choosefunction() is used to return a pointer to the function that corresponds
to the currently loaded missile. Checklocation sees if each location to shoot
is valid, and the location is skipped if it is not. Shootlocation actually
affects the board and hashmap.
*/

#include "turnfunctions.h"

/*static function for shooting locations. Full description at implementation*/
static void shootLocation(hashtable *ships, delimiters *delims, char **board, 
	int x, int y);



/*---------------------------------------------------------------------------|

PURPOSE:
	This function returns the function that corresponds to the currently 
	loaded missile. I am aware it is very poorly written. I had the impression
	it would be easier to add function pointers as specified. If I had more
	time, I would have a linkedlist of function pointers to go through.	
PARAMETERS:
	"list" the list of missiles to use to check the head's corresponding FP
RETURNS:
	A pointer to a function to use to shoot ships in the calling function.
BEHAVIOUR:
	This function checks for chars in the name of the head missile to see
	which function to return. Yes this is terrible but i was running out of
	time.*/

shootFP chooseFunction(linkedlist *list)
{
	/*int i;*/
	shootFP function;
	char comparator[6];

	memcpy(comparator, (char*)list->head->data, sizeof(char) * 6);

	if(comparator[1] == 'i')	/*check if single*/
	{
		function = &single;
	}
	else if(comparator[1] == 'p')/*check if splash*/
	{
		function = &splash;
	}
	else if(comparator[0] == 'v')/*check if vline*/
	{
		function = &vline;
	}
	else if(comparator[0] == 'h')/*check if hline*/
	{
		function = &hline;
	}
	else
	{
		perror("No matching missile found");
	}

	return function;
}


/*---------------------------------------------------------------------------|


PURPOSE:
	Shoots a single missile at the specified location
PARAMETERS:
	"ships" the hashmap to get ships from
	"delims" struct of variables to check for endgame with
	"board" the board of chars to display to the user
	"xloction" and "ylocation" the location of the ship to shoot
RETURNS:
	N/A
BEHAVIOUR:
	This function simply checks if the location is valid, and calls 
	shootlocation() on a single location if successful.
*/

void single(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation)
{
	if(checkLocation(board, ships, xlocation, ylocation)) 
	{
		shootLocation(ships, delims, board, xlocation, ylocation);
	}
}


/*---------------------------------------------------------------------------|

PURPOSE:
	Shoots a splash type missile at the specified location
PARAMETERS:
	"ships" the hashmap to get ships from
	"delims" struct of variables to check for endgame with
	"board" the board of chars to display to the user
	"xloction" and "ylocation" the location of the ship to shoot
RETURNS:
	N/A
BEHAVIOUR:
	This function increments through the 3x3 square of locations centred
	around the user-chosen location. For each of these 9 locations, they are
	checked for validity, and then shot. Locations that have already been
	shot or are not on the board are skipped using checkLocation();*/

void splash(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation)
{
	int i, j;
	/*for each x and y location in a 3x3 square...*/
	for(i = ylocation-1; i <= ylocation+1; i += 1)
	{
		for(j = xlocation-1; j <= xlocation+1; j++)
		{
			/*if location is within boundaries and has not already been shot*/
			if(checkLocation(board, ships, j, i)) 
			{
				shootLocation(ships, delims, board, j, i);
			}
		}	
	}
}



/*---------------------------------------------------------------------------|

PURPOSE:
	Shoots a verticle line of missiles at the specified location
PARAMETERS:
	"ships" the hashmap to get ships from
	"delims" struct of variables to check for endgame with
	"board" the board of chars to display to the user
	"xloction" and "ylocation" the location of the ship to shoot
RETURNS:
	N/A
BEHAVIOUR:
	This function iterates through all the locations in the provided y axis, 
	checks them for validity with checkLocation, and shoots them if they have
	not already been shot and are on the board*/

void vline(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation)
{
	int i;
	/*for each possible value for xlocation...*/
	for(i = 0; i<ships->boardheight; i++)
	{
		/*if location is within boundaries and has not already been shot*/
		if(checkLocation(board, ships, xlocation, i)) 
		{
			shootLocation(ships, delims, board, xlocation, i);
		}	
	}
}



/*---------------------------------------------------------------------------|

PURPOSE:
	Shoots a horizontal line of missiles at the specified location
PARAMETERS:
	"ships" the hashmap to get ships from
	"delims" struct of variables to check for endgame with
	"board" the board of chars to display to the user
	"xloction" and "ylocation" the location of the ship to shoot
RETURNS:
	N/A
BEHAVIOUR:
	This function iterates through all the locations in the provided x axis, 
	checks them for validity with checkLocation, and shoots them if they have
	not already been shot and are on the board*/

void hline(hashtable *ships, delimiters *delims, char **board, int xlocation, 
	int ylocation)
{
	int i;
	for(i = 0; i<ships->boardwidth; i++)
	{
		/*if location is within boundaries and has not already been shot*/
		if(checkLocation(board, ships, i, ylocation)) 
		{
			shootLocation(ships, delims, board, i, ylocation);
		}	
	}

}



/*---------------------------------------------------------------------------|

PURPOSE:
	This function checks if a given x and y location on the board is valid.
PARAMETERS:
	"board" the board to check
	"ships" the hashtable of ships to get board dimensions from
	"int x" and "int y" the x and y locations of the position to check
RETURNS:
	SUCCESS (1) if the location is valid
	FAILURE (0) if the location is invalid
BEHAVIOUR:
	The function first checks that the the location is within the dimensions
	of the board. Once that has been confirmed, it can safely check if the
	location has been shot previously. If all of these checks are valid,
	returns SUCCESS, else, returns FAILURE.*/

int checkLocation(char **board, hashtable *ships, int x, int y)
{
	int result;
	if(y < ships->boardheight 	&&
		x < ships->boardwidth	&&
		y >= 0					&&
		x >= 0					&&
		board[y][x] == UNKNOWN) 
	{
		result = SUCCESS;
	}
	else
	{
		result = FAILURE;
	}
	return result;
}


/*---------------------------------------------------------------------------|

PURPOSE:
	This function prints what each missile does. Used when a user enters !h
	when prompted to select a location to shoot
PARAMETERS:
	N/A
RETURNS:
	N/A
BEHAVIOUR:
	Simply prints each missile's functionality*/

void printMissileInfo(void)
{
	printf("MISSILE INFO:\n");
	printf(BLUE"single: "RESET"Hits a single tile\n");
	printf(BLUE"v-line: "RESET"Hits an entire column\n");
	printf(BLUE"h-line: "RESET"Hits an entire row\n");
	printf(BLUE"splash: "RESET"Hits a 3x3 square\n");
}



/*---------------------------------------------------------------------------|

PURPOSE:
	This function manipulates all the variables to change when a location has
	been shot and has been found to be valid.
PARAMETERS:
	"ships" hashmap of ships
	"delims" struct for variables to signify a game ending
	"board" list holding the status of each location
	"x" and "y" the location to shoot
RETURNS:
	N/A
BEHAVIOUR:
	This function changes everything that must be updates when a location is
	shot. Will check for hit or miss. Works by getting the corresponding ship
	to the location, and checking if it's length != 0. Uninitialised locations
	have length 0, and so if the length != 0, then there is a ship there. 
	Otherwise, the shot is a miss.*/

static void shootLocation(hashtable *ships, delimiters *delims, char **board, 
	int x, int y)
{
	ship *foundship;
	foundship = getShip(ships, x, y);

	if(foundship->length != 0)	/**ship found**/
	{
		/*print message and update variables*/
		printf("\n******* %sHIT!%s *******\n", RED, RESET);
		delims->nhits--;
		foundship->hitsleft--;
		board[y][x] = HIT;
		if(foundship->hitsleft == 0)
		{
			printf("\n%sSHIP DESTROYED: %s%s\n", RED, foundship->name, RESET);
		}
	}
	else						/**ship not found**/
	{
		printf("\n****** %sMISSED%s ******\n", BLUE, RESET);
		board[y][x] = MISS;
	}
}





