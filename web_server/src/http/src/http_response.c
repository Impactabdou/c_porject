#include "../include/http_response.h"
#include <stdlib.h>
#include <string.h>

void create_response(http_response *response, http_request *request) {
  response->request = request;
  response->data = calloc(1, sizeof(http_data));
}

void generate_response(const http_response *response,
                       char response_str[MAX_LEN]) {
  if (strncmp(response->request->h->methode, "GET", 3) == 0) {
    char header_response[MAX_LEN];
    size_t response_code = get_methode(response);
    get_header(response, response_code, header_response);
    strncpy(response_str, header_response, MAX_LEN - 1);
    strncat(response_str, response->data->data, response->data->data_size);
    return;
  }
}

void get_header(const http_response *response, size_t methode_response,
                char header_response[MAX_LEN]) {
  // Initialize header_response as empty string
  header_response[0] = '\0';

  // Build HTTP status line
  const char *http_response;
  switch (methode_response) {
  case 200:
    http_response = "200 OK";
    break;
  // Add other status codes as needed
  default:
    return;
  }

  // Calculate remaining space in header_response
  size_t remaining = MAX_LEN - 1; // Leave room for null terminator
  size_t written = 0;

  // Build response line by line with proper checks
  written = snprintf(header_response, remaining, "%s%s %s\r\n",
                     response->request->h->http_flag,
                     response->request->h->http_version, http_response);
  if (written >= remaining)
    return;
  remaining -= written;

  // Add content headers
  written = snprintf(header_response + strlen(header_response), remaining,
                     "Content-Type: text/html\r\n"
                     "Content-Length: %zu\r\n"
                     "\r\n",
                     response->data->data_size);
  if (written >= remaining) {
    // Truncation occurred - ensure null termination
    header_response[MAX_LEN - 1] = '\0';
  }
}
size_t read_file(FILE *fd, char content[MAX_LEN]) {
  char buffer[MAX_LINE] = {0};
  size_t content_size = 0;

  while (fgets(buffer, sizeof(buffer), fd) != NULL) {
    size_t remaining_space = MAX_LEN - content_size - 1;

    if (remaining_space <= 0) {
      break;
    }

    strncat(content, buffer, remaining_space);
    content_size += strlen(buffer);

    if (content_size >= MAX_LEN - 1) {
      break;
    }
  }
  content[content_size] = '\0';
  return content_size;
}

void prepare_path(const http_response *response,
                  char full_path[MAX_LEN_PARAM]) {
  const char public_path[MAX_LEN_PARAM] = "./public/";
  const char *index_path = "index.html";

  strncat(full_path, public_path, MAX_LEN_PARAM - 1);

  if (strncmp(response->request->h->path, "/", 1) == 0) {
    strncat(full_path, index_path, MAX_LEN_PARAM - 1);
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
    return 404;
  }

  char content[MAX_LEN] = {0};

  size_t content_size = read_file(fd, content);

  strncpy(response->data->data, content, content_size - 1);
  response->data->data_size = content_size;

  return 200;
}

void free_response(http_response *response) { free(response); }
