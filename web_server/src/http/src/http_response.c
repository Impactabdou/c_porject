#include "../include/http_response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

http_response *create_response(http_response *response, http_request *request) {
  response = calloc(1, sizeof(http_response));
  response->request = request;
  response->data = create_data(response->data);
  response->header = create_response_header(response->header, *request->h);
  response->response_str[0] = '\0';
  return response;
}

void generate_response(http_response *response) {

  if (strncmp(response->request->h->methode, GET, 3) == 0) {

    size_t response_code = get_methode(response);
    set_header_response(response->header, response_code);
    to_string_response_header(response->header);

    snprintf(response->response_str, RESPONSE_LEN - 1, "%s%s",
             response->header->header_str, response->data->data);
    response->response_str[RESPONSE_LEN - 1] = '\0';

    return;
  }
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

void prepare_path(const http_response *response,
                  char full_path[MAX_LEN_PARAM]) {

  strncat(full_path, PUBLIC_DIR, MAX_LEN_PARAM - 1);

  if (strncmp(response->request->h->path, "/", 1) == 0) {
    strncat(full_path, INDEX_HTML, MAX_LEN_PARAM - 1);
  } else {
    strncat(full_path, response->request->h->path, MAX_LEN_PARAM - 1);
  }

  full_path[MAX_LEN_PARAM - 1] = '\0';
}

size_t get_methode(const http_response *response) {

  char full_path[MAX_LEN_PARAM] = {0};

  prepare_path(response, full_path);

  FILE *fd = fopen(full_path, "r");
  if (fd == NULL) {
    perror("File not found");
    return NOT_FOUND;
  }

  char content[DATA_LEN] = {0};

  size_t content_size = read_file(fd, content);

  strncpy(response->data->data, content, content_size - 1);

  response->data->data_size = content_size;

  return CODE_OK;
}

void free_response(http_response *response) {
  free_http_response_header(response->header);
  free_data(response->data);
  response->header = NULL;
  response->data = NULL;
  response->request = NULL;
  free(response);
  response = NULL;
}
