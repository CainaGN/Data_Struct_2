CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o avl.o queue.o
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c  avl.h queue.h
	$(CC) $(CFLAGS) -c main.c


avl.o: avl.c avl.h 
	$(CC) $(CFLAGS) -c avl.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f $(OBJ) $(TARGET)

