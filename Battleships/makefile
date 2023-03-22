CC 		= gcc
CFLAGS 	= -std=c89 -Wall -g -pedantic -ansi -Werror #-D MONO#-D DEBUG
OBJECTS = main.o fileprocessing.o simulateturn.o \
			turnfunctions.o linkedlist.o hashtable.o turnsupports.o
LINKANDHASH = linkedlist/linkedlist.h hashtable/hashtable.h

#executable:
battleshipsgame : $(OBJECTS)
	$(CC) $(OBJECTS) -o battleshipsgame

#files:
main.o : main.c battleships.h $(LINKANDHASH)
	$(CC) $(CFLAGS) -c main.c

simulateturn.o : simulateturn.c battleships.h $(LINKANDHASH)
	$(CC) $(CFLAGS) -c simulateturn.c

fileprocessing.o : fileprocessing.c battleships.h $(LINKANDHASH)
	$(CC) $(CFLAGS) -c fileprocessing.c

turnsupports.o : turnsupports.c battleships.h $(LINKANDHASH)
	$(CC) $(CFLAGS) -c turnsupports.c

turnfunctions.o : turnfunctions/turnfunctions.c battleships.h \
$(LINKANDHASH) turnfunctions/turnfunctions.h
	$(CC) $(CFLAGS) -c turnfunctions/turnfunctions.c

linkedlist.o : linkedlist/linkedlist.c linkedlist/linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist/linkedlist.c

hashtable.o : hashtable/hashtable.c hashtable/hashtable.h
	$(CC) $(CFLAGS) -c hashtable/hashtable.c


clean:
	rm -f battleshipsgame $(OBJECTS)


