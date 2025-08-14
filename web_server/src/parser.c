#include "../include/parser.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

parser create_parser(char request[MAX_LEN]) {
  parser p;

  return p;
}

void create_header(header *h, const char request[MAX_LEN]) {

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
    return;
  }

  h = (header *)calloc(1, sizeof(header));

  parse_header(h, request_header);
}

void parse_header(header *h, char request_header[MAX_LEN]) {

  char value[MAX_LEN_PARAM] = {0};
  char key[MAX_LEN_PARAM] = "Accept-Language\0";

  if (parse_key(request_header, key, value) == 0) {
    printf("%s\n", value);
  } else {
    perror("Something went wrong : ");
  }
  exit(1);
}

int parse_methode(const char request_header[MAX_LEN_PARAM]);

/*
 * @brief takes an http header key and sets it's value
 */
int parse_key(const char string[MAX_LEN_PARAM], const char key[MAX_LEN_PARAM],
              char value[MAX_LEN_PARAM]) {

  if (string == NULL || key == NULL) {
    fprintf(stderr, "Key or String are NULL\n");
    return 1;
  }

  size_t key_size = strlen(key);
  printf("%ld\n", key_size);
  size_t string_size = strlen(string);
  size_t string_index = 0;
  char temp[MAX_LEN_PARAM] = {0};
  bool key_found = false;

  while (string_index < string_size) {
    /* Parsing key */
    size_t temp_index = 0;
    memset(temp, 0, sizeof(temp));
    while (string[string_index] != ':') {
      temp[temp_index++] = string[string_index++];
    }
    temp[temp_index] = '\0';

    if (strncmp(key, temp, key_size) == 0) {
      key_found = true;
      break;
    }

    while (string_index < string_size && string[string_index] != '\r' &&
           string[string_index + 1] != '\n')
      string_index++;
    string_index += 2;
  }
  if (!key_found) {
    fprintf(stderr, "Key has not been found in string\n");
    return 2;
  }
  size_t value_index = strlen(value);
  for (size_t i = string_index; i < string_size; i++) {
    if (string[i] == '\r' && string[i + 1] == '\n') {
      break;
    }
    value[value_index++] = string[i];
  }
  value[value_index] = '\0';

  return 0;
}
