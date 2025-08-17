#ifndef H_REQ
#define H_REQ
#include "../../../include/shared.h"
#include "http_data.h"
#include "http_header.h"

typedef struct http_request {
  http_request_header *h;
  http_data *data;
} http_request;

http_request *create_request(http_request *req, char req_str[MAX_LEN]);

void free_request(http_request *request);

#endif
