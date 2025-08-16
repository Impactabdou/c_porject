#ifndef H_REQ
#define H_REQ
#include "../../../include/shared.h"
#include "http_data.h"
#include "http_header.h"

typedef struct http_request {
  const header *h;
  const http_data *data;
} http_request;

void create_request(http_request *req, header *h, http_data *data,
                    const char req_str[MAX_LEN]);

void free_request(http_request *request);
#endif
