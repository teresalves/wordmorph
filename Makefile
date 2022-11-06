#
#  File name: makefile
#
#  Author: 2013 Fall Semester AED Team
#
#  Release date: 2013/11/02
#
#  Description: Makefile for the individual evaluation laboratory
#
#  Usage:
#     1) To generate the executable file for the program wordmorph, run
#         $ make wd
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#
#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -O3

#  Objects
OBJECTS = main.o heaps.o utils.o graph.o files.o

wordmorph: $(OBJECTS)
	$(CC) $(CFLAGS) -o wordmorph $(OBJECTS)

main.o: main.c utils.h
	$(CC) -c $(CFLAGS) main.c

heaps.o: heaps.c heaps.h
	$(CC) -c $(CFLAGS) heaps.c

utils.o: utils.c utils.h graph.h files.h
	$(CC) -c $(CFLAGS) utils.c

graph.o: graph.c graph.h utils.h heaps.h
	$(CC) -c $(CFLAGS) graph.c

files.o: files.c files.h utils.h
	$(CC) -c $(CFLAGS) files.c

clean::
	rm -f *.o core a.out wordmorph *~

# DO NOT DELETE
