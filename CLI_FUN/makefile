# Makefile for a C program

# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files
SRC = main.c chess.c
OBJ = $(SRC:.c=.o)

# Output executable
EXECUTABLE = myprogram

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c source files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJ)
