#include "../include/http_request.h"

http_request *create_request(http_request *req, char req_str[MAX_LEN]) {
  req = calloc(1, sizeof(http_request));
  req->h = create_request_header(req->h, req_str);
  print_request_header(*req->h);
  req->data = create_data(req->data);
  return req;
}

void free_request(http_request *request) {
  free_request_header(request->h);
  free_data(request->data);
  request->data = NULL;
  request->h = NULL;
  free(request);
  request = NULL;
}
