/*
FILENAME:	hashtable.c
AUTHOR:		Jye Tremlett
STUDENT #:	20217987
UNIT:		COMP1000
MODIFIED:	22/05/2020
PURPOSE:	

Custom hashtable implementation. Works by maintaining an array of pointers 
to "ship" structs, which contain info ships. Ships can be accessed using a 
hashing algorithm thatmaps a location on a board, e.g. 'A1', to a unique 
location in the array of pointers to ships. If a ship spans several board 
locations, the corresponding cells of the array will point to the same 
"ship" struct.

This file includes functions for creating ships, creating a new table, adding
a ship, getting a ship, and freeing the table.
*/

#include "hashtable.h"



/*--------------------------------------------------------------------------|

PURPOSE:	
	Creates a new ship as per the attributes passed as parameters.
	Checking of values' validity is done in fileprocessing.c by checkIfValid()
PARAMETERS:	
	"name": string name of the ship
	"direction": n, s, e, or w, being the direction the ship faces
	"xlocation": char respresenting the x axis location the ship occupies on
	the grid
	"ylocation": int representing the y axis location of the ship 
	"length": int length of the ship
RETURNS:
	A ship struct populated with the parameter values	
BEHAVIOUR:
	Takes parameter values and populates a new "ship" struct variablewith 
	those values. Then returns the new ship.*/

ship createShip(char name[MAX_NAME_LENGTH], char direction, char xlocation, 
	int ylocation, int length)
{	
	ship newship;
	strcpy(newship.name, name);
	newship.direction = toupper(direction);
	newship.xlocation = toupper(xlocation);
	newship.hitsleft  = length;
	newship.length 	  = length;
	newship.ylocation = ylocation;

	return newship;
}


/*--------------------------------------------------------------------------|

PURPOSE:
	Initialises a new table, declared in calling function.
PARAMETERS:
	"Width" and "height" = width and height of the list storing ship pointers,
	"newtable" = pointer to new table declared in calling function
RETURNS:
	N/A
BEHAVIOUR:
	This function initialises newtable->list with a width*height array of 
	"empty" ship structs. Then initialises the "boardwidth" and "boardheight"
	variables of the hashtable struct.*/

void newTable(int width, int height, hashtable *newtable)
{
	int i, size;
	ship emptyship;

	emptyship = createShip("uninit", 'S', 'A', 0, 0);
	size = width*height;
	newtable->list = (ship**)malloc(size * sizeof(ship*));
	if(newtable->list == NULL)
	{
		perror("Error allocating list in hashtable\n");
	}
	for(i = 0; i < size; i++)
	{
		newtable->list[i] = (ship*)malloc(sizeof(ship));
		if(newtable->list[i] == NULL)
		{
			perror("Error allocating list value when creating new list\n");
		}
		*newtable->list[i] = emptyship;
	}
	newtable->boardwidth  = width;
	newtable->boardheight = height;

}


/*--------------------------------------------------------------------------|

PURPOSE:
	To add a ship to a hashtable, both of which are defined in the calling 
	function.
PARAMETERS:
	"table" = table to add the ship to, and "ship" = the ship to add. This
	ship has already been declared and initialised with createShip().
RETURNS:
	Returns SUCCESS(1) for success and FAILURE(0) for failure.
BEHAVIOUR:
	This function first establishes an "offset", by which each consecutive
	position in the hashtable will be made to point to the new ship. The
	idea here is that if a ship is to cover A1, A2, and A3, the corresponding
	locations in the hashtable will all point to the same ship.

	So, via the for loop, each table location that will point to the new ship
	is calculated and the address in the hashmap->list is made to point to it.
	Since every unpopulated location is filled with an "empty" ship of length
	0, we can know that if a location we want to give to a new ship has a 
	length != 0, the ship overlaps with another and is therfore invalid.*/

int addShip(hashtable *table, ship *newship)
{
	int i, tablelocation, offset, width, result;
	char direction;

	result = SUCCESS;
	width = table->boardwidth;

	/**find the offset for the locations**/
	direction = newship->direction;
	if(direction == 'N')		/**if ship points down**/
	{
		offset = width;
	}
	else if(direction == 'S')	/**if ship points up**/
	{
		offset = (-1)*width;
	}
	else if(direction == 'E')	/**if ship points right**/
	{
		offset = -1;
	}
	else if(direction == 'W')	/**if ship points left**/
	{
		offset = 1;
	}

	/**assign the location of the ship head + i*offset to the hashtable:**/
	for(i = 0; i < newship->length; i++)
	{
		tablelocation = HASH_ALG((int)newship->xlocation-65, newship->ylocation-1, 
			table->boardwidth);

		/**if the spot is already occupied, FAILURE**/
		if(table->list[tablelocation + i*offset]->length != 0)
		{		
			perror("Ship overlaps with another existing ship");
			result = FAILURE;
		}

		/**overwrite location with new ship**/
		free(table->list[tablelocation + i*offset]);
		table->list[tablelocation + i*offset] = newship;
	}
	return result;
}


/*--------------------------------------------------------------------------|

PURPOSE:
	This function returns a pointer to a ship found at a given location. This
	pointer can then be manipulated, which permeates to the actual ship in the
	hashtable.
PARAMETERS:
	"table" = the table to get the ship from, "xlocation" and "ylocation" are
	the x and y coordinates for the ship.
RETURNS:
	A pointer to a ship that can then be manipulated by the calling function.
BEHAVIOUR:
	The function first using the hashing algorithm to get the index that 
	corresponds to the provided x and y locations. Then, a pointer to the ship
	found at that location is returned.*/

ship* getShip(hashtable *table, int xlocation, int ylocation)
{
	int index;
	ship *foundship;

	index = HASH_ALG(xlocation, ylocation, table->boardwidth);
	if(table->list[index] != (NULL))
	{
		foundship = table->list[index];
	}
	return foundship;
}

/*--------------------------------------------------------------------------|

PURPOSE:
	To free() each ship in the hashtable, and the hashtable once no longer 
	needed.
PARAMETERS:
	"table" = the table to free
RETURNS:
	N/A
BEHAVIOUR:
	This function works by freeing ships if and only if their length == 0, 
	otherwise length is decremented by 1. By doing this, we eliminate the risk
	of attempting to free the same ship multiple times, since multiple array 
	addresses point to the same ship.*/

void freeTable(hashtable *table)
{
	int size, i;
	size = table->boardheight * table->boardwidth;
	for(i = 0; i<size; i++)
	{
		/*if ship length == 0, free the ship*/
		if(table->list[i]->length == 0)
		{
			free(table->list[i]);
		}
		/*else, decrement that ship's length*/
		else
		{
			table->list[i]--;
		}
	}
	free(table->list);
}

