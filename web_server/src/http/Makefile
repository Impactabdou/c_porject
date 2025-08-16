# HTTP Component Directories
HTTP_SRC_DIR = $(HTTP_DIR)/src
HTTP_OBJ_DIR = $(HTTP_DIR)/obj
HTTP_BIN_DIR = $(HTTP_DIR)/bin
HTTP_INC_DIR = $(HTTP_DIR)/include

# HTTP Source Files
HTTP_SRCS = $(wildcard $(HTTP_SRC_DIR)/*.c)
HTTP_OBJS = $(patsubst $(HTTP_SRC_DIR)/%.c,$(HTTP_OBJ_DIR)/%.o,$(HTTP_SRCS))

# HTTP-specific flags
HTTP_CPPFLAGS = -I$(HTTP_INC_DIR) -I$(INC_DIR)
HTTP_CFLAGS = -Wall -Wextra -O2

.PHONY: http http_clean http_distclean

http: $(HTTP_OBJ_DIR) $(HTTP_BIN_DIR) $(HTTP_TARGET)

$(HTTP_TARGET): $(HTTP_OBJS)
	$(CC) $(HTTP_CFLAGS) $(HTTP_CPPFLAGS) -o $@ $^ $(OBJ_DIR)/shared.o

$(HTTP_OBJ_DIR)/%.o: $(HTTP_SRC_DIR)/%.c | $(HTTP_OBJ_DIR)
	$(CC) $(HTTP_CFLAGS) $(HTTP_CPPFLAGS) -c $< -o $@

$(HTTP_BIN_DIR) $(HTTP_OBJ_DIR):
	$(MKDIR) $@

http_clean:
	-@$(RM) $(HTTP_OBJ_DIR)/*.o

http_distclean: http_clean
	-@$(RM) $(HTTP_TARGET)
