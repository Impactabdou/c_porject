#include "../include/http_data.h"
#include <stdio.h>
#include <string.h>

http_data *create_data(http_data *data) {
  data = calloc(1, sizeof(http_data));
  data->data_size = 0;
  data->data[0] = '\0';
  return data;
}

http_data *create_data_from_file(const char *path) {
  http_data *data = NULL;
  data = create_data(data);
  FILE *fd = fopen(path, "r");
  if (fd == NULL) {
    perror("File not found or something went wrong while opening the file ");
    return NULL;
  }
  read_file(fd, data->data);
  return data;
}

size_t read_file(FILE *fd, char content[DATA_LEN]) {
  char buffer[MAX_LINE] = {0};
  size_t content_size = 0;

  while (fgets(buffer, sizeof(buffer), fd) != NULL) {
    size_t remaining_space = DATA_LEN - content_size - 1;

    if (remaining_space <= 0) {
      break;
    }

    strncat(content, buffer, remaining_space);
    content_size += strlen(buffer);

    if (content_size >= DATA_LEN - 1) {
      break;
    }
  }
  content[content_size] = '\0';
  return content_size;
}

void free_data(http_data *data) {
  free(data);
  data = NULL;
}
