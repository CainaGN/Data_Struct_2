CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o linked_list.o tree.o queue.o
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c linked_list.h tree.h queue.h
	$(CC) $(CFLAGS) -c main.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

tree.o: tree.c tree.h linked_list.h
	$(CC) $(CFLAGS) -c tree.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f $(OBJ) $(TARGET)
