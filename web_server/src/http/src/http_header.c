#include "../include/http_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

http_request_header *create_request_header(http_request_header *h,
                                           const char request[MAX_LEN]) {

  char request_header[MAX_LEN] = {0};
  bool break_found = false;
  size_t r_h_size = 0;

  for (r_h_size = 0; r_h_size < strlen(request); r_h_size++) {
    if (request[r_h_size] == '\r' && request[r_h_size + 1] == '\n' &&
        request[r_h_size + 2] == '\r' && request[r_h_size + 3] == '\n') {
      break_found = true;
      break;
    }
    request_header[r_h_size] = request[r_h_size];
  }
  request_header[r_h_size] = '\0';

  if (!break_found) {
    fprintf(stderr, "No break has been found in the request\n");
    return NULL;
  }

  h = calloc(1, sizeof(http_request_header));

  set_methode(h, request);

  h->number_params = HEADER_DEFAULT_NUMBER_PARAMS;

  char sanitised_header[MAX_LEN];

  sanitise_input(request_header, sanitised_header);

  set_request_header(h, sanitised_header);

  return h;
}

void set_request_header(http_request_header *h, char request_header[MAX_LEN]) {
  char keys[HEADER_DEFAULT_NUMBER_PARAMS][MAX_LEN_PARAM] = {
      ACCEPT, ACCEPT_ENCODING, ACCEPT_LANG, HOST, CONNECTION, USER_AGENT};
  char values[HEADER_DEFAULT_NUMBER_PARAMS][MAX_LEN_PARAM] = {0};

  bool not_found = false;

  for (size_t i = 0; i < HEADER_DEFAULT_NUMBER_PARAMS; i++) {
    if (parse_request_header_params(request_header, keys[i], values[i]) != 0) {
      not_found = true;
    }
  }

  if (not_found) {
    printf("/!\\ All or Some header fields have not been initialized\n");
  }

  strncpy(h->accept, values[0], sizeof(h->accept) - 1);
  h->accept[sizeof(h->accept) - 1] = '\0';

  strncpy(h->accept_encoding, values[1], sizeof(h->accept_encoding) - 1);
  h->accept_encoding[sizeof(h->accept_encoding) - 1] = '\0';

  strncpy(h->accept_language, values[2], sizeof(h->accept_language) - 1);
  h->accept_language[sizeof(h->accept_language) - 1] = '\0';

  strncpy(h->host, values[3], sizeof(h->host) - 1);
  h->host[sizeof(h->host) - 1] = '\0';

  strncpy(h->connection, values[4], sizeof(h->connection) - 1);
  h->connection[sizeof(h->connection) - 1] = '\0';

  strncpy(h->user_agent, values[5], sizeof(h->user_agent) - 1);
  h->user_agent[sizeof(h->user_agent) - 1] = '\0';
}

void set_methode(http_request_header *h,
                 const char request_header[MAX_LEN_PARAM]) {
  char methode[MAX_LEN_PARAM] = {0};
  char path[MAX_LEN_PARAM] = {0};
  char http_flag[MAX_LEN_PARAM] = {0};
  char version[MAX_LEN_PARAM] = {0};
  char methode_clean[MAX_LEN_PARAM] = {0};
  char path_clean[MAX_LEN_PARAM] = {0};
  char http_flag_clean[MAX_LEN_PARAM] = {0};
  char version_clean[MAX_LEN_PARAM] = {0};

  size_t req_index = 0;
  size_t temp_index = 0;

  while ((methode[temp_index++] = request_header[req_index++]) != 32)
    ;
  methode[temp_index] = '\0';
  temp_index = 0;

  while ((path[temp_index++] = request_header[req_index++]) != 32)
    ;

  path[temp_index] = '\0';
  temp_index = 0;

  while ((http_flag[temp_index++] = request_header[req_index++]) != 47)
    ;

  http_flag[temp_index] = '\0';
  temp_index = 0;

  while ((version[temp_index++] = request_header[req_index++]) != '\r' &&
         request_header[req_index + 1] != '\n')
    ;

  version[temp_index] = '\0';

  sanitise_input(methode, methode_clean);
  sanitise_input(path, path_clean);
  sanitise_input(http_flag, http_flag_clean);
  sanitise_input(version, version_clean);

  strncpy(h->methode, methode_clean, strlen(methode));
  strncpy(h->path, path_clean, strlen(path));
  strncpy(h->http_version, version_clean, strlen(version));
  strncpy(h->http_flag, http_flag_clean, strlen(http_flag));
}

/*
 * @brief takes an http header key and sets it's value
 */
int parse_request_header_params(const char header[MAX_LEN_PARAM],
                                const char key[MAX_LEN_PARAM],
                                char value[MAX_LEN_PARAM]) {

  if (header == NULL || key == NULL) {
    fprintf(stderr, "Key or String are NULL\n");
    return 1;
  }

  size_t key_size = strlen(key);
  size_t string_size = strlen(header);
  size_t string_index = 0;
  char temp[MAX_LEN_PARAM] = {0};
  bool key_found = false;

  while (string_index < string_size) {
    /* Parsing key */
    size_t temp_index = 0;
    memset(temp, 0, sizeof(temp));
    while (header[string_index] != ':') {
      temp[temp_index++] = header[string_index++];
    }
    temp[temp_index] = '\0';

    if (strncmp(key, temp, key_size) == 0) {
      key_found = true;
      break;
    }

    while (string_index < string_size && header[string_index] != '\r' &&
           header[string_index + 1] != '\n')
      string_index++;
    string_index += 2;
  }
  if (!key_found) {
    fprintf(stderr, "Key has not been found in string\n");
    return 2;
  }
  size_t value_index = strlen(value);

  /* shiffting to remove ':' */
  ++string_index;

  for (size_t i = string_index; i < string_size; i++) {
    if (header[i] == '\r' && header[i + 1] == '\n') {
      break;
    }
    value[value_index++] = header[i];
  }
  value[value_index] = '\0';

  return 0;
}

void print_request_header(http_request_header h) {
  printf("%s %s %s%s\n", h.methode, h.path, h.http_flag, h.http_version);
  printf("Accept: %s\n"
         "Accept-Language: %s\n"
         "Accept-Encoding: %s\n"
         "Host: %s\n"
         "User-Agent: %s\n"
         "Connection: %s\n",
         h.accept, h.accept_language, h.accept_encoding, h.host, h.user_agent,
         h.connection);
}

void free_request_header(http_request_header *header) {
  free(header);
  header = NULL;
}

http_response_header *
create_response_header(http_response_header *response_header,
                       http_request_header request_header) {
  response_header = calloc(1, sizeof(http_response_header));
  snprintf(response_header->http_version, sizeof(response_header->http_version),
           "%s", request_header.http_version);

  snprintf(response_header->response_status,
           sizeof(response_header->response_status), "200 OK");

  generate_date(response_header->date);

  response_header->header_str[0] = '\0';

  return response_header;
}

void generate_date(char buffer[MAX_LEN_PARAM]) {
  FILE *fd = NULL;
  fd = popen("date", "r");
  if (fd == NULL) {
    perror("Date command could not be exec ");
    return;
  }
  if (fgets(buffer, MAX_LEN_PARAM - 1, fd) == NULL) {
    perror("Failed to read DATE output ");
  }
  buffer[MAX_LEN_PARAM - 1] = '\0';
  pclose(fd);
}

void set_header_response(http_response_header *response_header,
                         size_t response_code) {

  switch (response_code) {
  case CODE_OK:
    snprintf(response_header->response_status, 7, "200 OK");
    ;
    break;
  case NOT_FOUND:
    snprintf(response_header->response_status, 4, "404");
    break;
  // Add other status codes as needed
  default:
    return;
  }
  // here to add other headers to set dont forget to add them in the
  // http_response_header structur too
}

void to_string_response_header(http_response_header *response_header) {

  snprintf(response_header->header_str, MAX_LEN - 1,
           "HTTP/%s %s\r\nContent-Type: %s\r\nDate: %s\r\n\r\n",
           response_header->http_version, response_header->response_status,
           response_header->content_type, response_header->date);

  response_header->header_str[MAX_LEN - 1] = '\0';
}

void free_http_response_header(http_response_header *header) {
  free(header);
  header = NULL;
}
