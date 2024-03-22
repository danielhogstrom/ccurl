# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Source files
SRC = main.c

# Object files
OBJ = $(SRC:.c=.o)

# Target executable
TARGET = ccurl

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
