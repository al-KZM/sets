CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
SRC_DIR=my_set
OUT_DIR=out

all:my_set.o set.o
	$(CC) my_set.o set.o -o $(OUT_DIR)/set

my_set.o: set.o $(SRC_DIR)/my_set.c $(SRC_DIR)/my_set.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/my_set.c

set.o: $(SRC_DIR)/set.c $(SRC_DIR)/set.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/set.c




