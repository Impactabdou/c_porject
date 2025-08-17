# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -ansi -std=c99 -lnsl -lm
LDFLAGS =
DOXYGEN = doxygen

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = docs
INC_DIR = include

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BIN = $(BIN_DIR)/my_program

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Doxygen documentation
docs:
	$(DOXYGEN) Doxyfile

# Git push
push:
	git push

# Git commit
commit:
	git add .
	git commit -m "$(COM)" 

# Run elf
r:
	./bin/my_program

# Phony targets
.PHONY: all clean docs

