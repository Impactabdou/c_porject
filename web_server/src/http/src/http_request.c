#include "../include/http_request.h"

http_request *create_request(http_request *req, char req_str[MAX_LEN]) {
  req = calloc(1, sizeof(http_request));
  if ((req->h = create_request_header(req->h, req_str)) == NULL) {
    return NULL;
  }
  print_request_header(*req->h);
  req->data = create_data(req->data);
  return req;
}

void free_request(http_request *request) {

  if (request != NULL) {
    if (request->h != NULL) {
      free_request_header(request->h);
      request->h = NULL;
    }
    if (request->data != NULL) {
      free_data(request->data);
      request->data = NULL;
    }

    free(request);
    request = NULL;
  }
}
