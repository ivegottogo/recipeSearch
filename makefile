CC = gcc
FLAGS = -g -Wall -Wextra
TARGET = main
EXEC = ./$(TARGET)

default: build

all: build run

run :
	$(EXEC) $(ARGS)

build : link
	$(CC) $(FLAGS) main.c openFile.o linkedlist.o statistiques.o -o $(TARGET)

link : openFile.c openFile.h linkedlist.c linkedlist.h statistiques.c statistiques.h
	$(CC) $(FLAGS) -c -g openFile.c linkedlist.c statistiques.c
