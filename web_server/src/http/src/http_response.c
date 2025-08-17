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

    if (response_code == CODE_OK) {
      set_header_response(response->header, GET);
      to_string_response_header(response->header);
      snprintf(response->response_str, RESPONSE_LEN - 1, "%s%s",
               response->header->header_str, response->data->data);
      response->response_str[RESPONSE_LEN - 1] = '\0';
    } else {
      set_response_error_data(response, response_code);
      generate_generic_response(response, response_code);
    }

    return;
  }
}

void set_response_error_data(http_response *response, size_t error_code) {
  if (response->data != NULL)
    free_data(response->data);
  switch (error_code) {
  case NOT_FOUND:
    response->data = create_data_from_file(PATH_NOT_FOUND);
    break;
  default:
    printf("In set_response_error_data/http_response.c error case is not "
           "handled FAILED TO RESPOND\n");
    exit(1);
  }
}

void generate_generic_response(http_response *response, size_t error_code) {
  char date[MAX_LEN_PARAM] = {0};
  char header_str[MAX_LEN] = {0};
  generate_date(date);
  snprintf(header_str, MAX_LEN - 1,
           "HTTP/1.1 %zu\r\nContent-Type: text/html\r\nDate: %s\r\n\r\n",
           error_code, date);
  snprintf(response->response_str, RESPONSE_LEN - 1, "%s%s", header_str,
           response->data->data);
  response->response_str[RESPONSE_LEN - 1] = '\0';
}

void prepare_path(const http_response *response,
                  char full_path[MAX_LEN_PARAM]) {

  strncat(full_path, PUBLIC_DIR, MAX_LEN_PARAM - 1);

  if (strncmp(response->request->h->path, "/",
              strlen(response->request->h->path)) == 0) {
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

http_response *create_response_for_bad_request(const char *path) {
  http_response *res = calloc(1, sizeof(http_response));
  res->header = NULL;
  res->data = create_data_from_file(path);
  return res;
}

void free_response(http_response *response) {
  if (response != NULL) {
    if (response->header != NULL) {
      free_http_response_header(response->header);
      response->header = NULL;
    }
    if (response->data != NULL) {
      free_data(response->data);
      response->data = NULL;
    }
    if (response->request != NULL) {
      response->request = NULL;
    }

    free(response);
    response = NULL;
  }
}
