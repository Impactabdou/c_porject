#ifndef H_REQ_DATA
#define H_REQ_DATA
#include "../../../include/shared.h"
#include "stdlib.h"

typedef struct http_data {
  char data[MAX_LEN];
  size_t data_size;
} http_data;

void create_data(http_data *data, const char req[MAX_LEN]);

void free_data(http_data *data);

#endif
