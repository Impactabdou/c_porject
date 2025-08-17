#ifndef H_REQ_DATA
#define H_REQ_DATA
#include "../../../include/shared.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct http_data {
  char data[DATA_LEN];
  size_t data_size;
} http_data;

http_data *create_data(http_data *data);

http_data *create_data_from_file(const char *path);

size_t read_file(FILE *fd, char content[DATA_LEN]);

void free_data(http_data *data);

#endif
