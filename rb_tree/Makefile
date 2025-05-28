CC = gcc
CFLAGS = -Wall 

OBJS = main.o rb_tree.o 

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.c rb_tree.h 
	$(CC) $(CFLAGS) -c main.c

rb_tree.o: rb_tree.c rb_tree.h 
	$(CC) $(CFLAGS) -c rb_tree.c



clean:
	rm -f *.o main

