#include "../include/http_response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_response(http_response *response, http_request *request) {
  response->request = request;
}

void generate_response(const http_response *response) {
  if (strncmp(response->request->h->methode, "GET", 3) == 0) {
  }
}

void get_methode(const http_response response) {

  const char public_path[MAX_LEN_PARAM] = "./public\0";
  char full_path[MAX_LEN_PARAM] = {0};
  strncat(full_path, public_path, sizeof(full_path) - 1);
  strncat(full_path, response.request->h->path, sizeof(full_path) - 1);
  full_path[sizeof(full_path) - 1] = '\0';

  FILE *fd = fopen(response.request->h->path, "r");
  if (fd == NULL) {
    perror("File not found");
    return;
  }

  char content[MAX_LEN] = {0};
  char buffer[MAX_LINE] = {0};
  size_t content_size = 0;

  while (!fgets(buffer, MAX_LINE, fd)) {
    strncat(content, buffer, sizeof(content) - 1);
    content_size += strlen(buffer);
  }

  content[content_size] = '\0';

  printf("%s\n", content);
}

void free_response(http_response *response) { free(response); }
