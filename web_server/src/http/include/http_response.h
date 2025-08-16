#ifndef H_RESPONSE
#define H_RESPONSE
#include "http_data.h"
#include "http_header.h"
#include "http_request.h"
typedef struct http_response {
  http_request *request;
} http_response;

void create_response(http_response *response, http_request *request);

void generate_response(const http_response *response);

void free_response(http_response *response);

#endif
