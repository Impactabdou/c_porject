#ifndef H_RESPONSE
#define H_RESPONSE
#include "http_data.h"
#include "http_header.h"
#include "http_request.h"
#include <stdio.h>

#define PUBLIC_DIR "./public/"
#define INDEX_HTML "./index.html"

typedef struct http_response {
  http_request *request;
  http_data *data;
  http_response_header *header;
  char response_str[RESPONSE_LEN];
} http_response;

http_response *create_response(http_response *response, http_request *request);

void generate_response(http_response *response);

size_t get_methode(const http_response *response);

void prepare_path(const http_response *response, char full_path[MAX_LEN_PARAM]);

void get_header(const http_response *response, size_t methode_response,
                char header_response[MAX_LEN]);

void generate_generic_response(http_response *response, size_t error_code);

http_response *create_response_for_bad_request(const char *path);

void set_response_error_data(http_response *response, size_t error_code);

void free_response(http_response *response);

#endif
