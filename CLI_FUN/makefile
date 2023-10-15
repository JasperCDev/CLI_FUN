# Makefile for a C program

# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files and output executable
SRC = main.c
EXECUTABLE = myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
		$(CC) $(CFLAGS) -o $@ $^

clean:
		rm -f $(EXECUTABLE)
