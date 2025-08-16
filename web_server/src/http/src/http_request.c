#include "../include/http_request.h"

void create_request(http_request *req, header *h, http_data *data,
                    const char req_str[MAX_LEN]) {

  create_header(h, req_str);
  create_data(data, req_str);

  req->h = h;

  req->data = data;
}

void free_request(http_request *request) { free(request); }
