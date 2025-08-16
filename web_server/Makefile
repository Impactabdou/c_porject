# Tool# Tools
CC = gcc
RM = rm -f
MKDIR = mkdir -p

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
INC_DIR = ./include
HTTP_DIR = $(SRC_DIR)/http
HTTP_SRC_DIR = $(HTTP_DIR)/src
HTTP_OBJ_DIR = $(OBJ_DIR)/http

# Compilation flags
CPPFLAGS = -I$(INC_DIR) -I$(HTTP_DIR)/include
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

# Targets
PROG = $(BIN_DIR)/web_server

# Source files
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.c)
HTTP_SRCS = $(wildcard $(HTTP_SRC_DIR)/*.c)

# Object files
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
HTTP_OBJS = $(patsubst $(HTTP_SRC_DIR)/%.c,$(HTTP_OBJ_DIR)/%.o,$(HTTP_SRCS))
OBJS = $(MAIN_OBJS) $(HTTP_OBJS)

.PHONY: all clean distclean

all: $(HTTP_OBJ_DIR) $(BIN_DIR) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(HTTP_OBJ_DIR)/%.o: $(HTTP_SRC_DIR)/%.c | $(HTTP_OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(HTTP_OBJ_DIR):
	$(MKDIR) $@

clean:
	-@$(RM) $(OBJ_DIR)/*.o
	-@$(RM) $(HTTP_OBJ_DIR)/*.o

distclean: clean
	-@$(RM) $(PROG)
