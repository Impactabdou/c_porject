#include "../include/http_data.h"
#include <stdlib.h>

http_data *create_data(http_data *data) {
  data = calloc(1, sizeof(http_data));
  data->data_size = 0;
  data->data[0] = '\0';
  return data;
}

void free_data(http_data *data) {
  free(data);
  data = NULL;
}
