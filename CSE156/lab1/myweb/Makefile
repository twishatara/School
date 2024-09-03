# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -g

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/myweb.c
OBJ = $(SRC:.c=.o)

# Executable name and its directory
EXEC = myweb
BIN_DIR = bin

# Default target
all: $(EXEC)

# Rule for making the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(BIN_DIR)/$(EXEC)

# Rule for making object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean command to remove generated files
clean:
	rm -f $(SRC_DIR)/*.o $(BIN_DIR)/$(EXEC)

# Phony targets
.PHONY: all clean

