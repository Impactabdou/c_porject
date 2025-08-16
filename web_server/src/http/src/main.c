#include "../include/http_response.h"
#include <stdio.h>

int main() {

  const char request[MAX_LEN] =
      "GET / HTTP/1.1\r\n"
      "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:141.0) \r\n"
      "Gecko/20100101 Firefox/141.0\r\n"
      "Accept: "
      "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
      "Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
      "Accept-Encoding: gzip, deflate, br, zstd\r\n"
      "Sec-GPC: 1\r\n"
      "Connection: keep-alive\r\n"
      "Upgrade-Insecure-Requests: 1\r\n"
      "Sec-Fetch-Dest: document\r\n"
      "Sec-Fetch-Mode: navigate\r\n"
      "Sec-Fetch-Site: none\r\n\r\n";

  http_request req;
  header h;
  http_data data;
  http_request http_request;
  http_response http_response;

  printf("=================================\n");
  create_request(&http_request, &h, &data, request);
  print_header(h);
  create_response(&http_response, &http_request);
  generate_response(&http_response);
  printf("=================================\n");

  return 0;
}
