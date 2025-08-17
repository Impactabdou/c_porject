// #include "../include/http_response.h"
// #include <stdio.h>
//
// int main() {
//
//   char buffer[MAX_LEN] =
//       "GET / HTTP/1.1\r\n"
//       "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:141.0) \r\n"
//       "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
//       "Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
//       "Sec-Fetch-Site: none\r\n\r\n";
//   char bad_req[MAX_LEN] = "GET / HTTP/1.1\r\n\r\n";
//
//   http_request *request = NULL;
//   http_response *response = NULL;
//   printf("%s\n", bad_req);
//   printf("=================================\n");
//
//   if ((request = create_request(request, bad_req)) == NULL) {
//     response = create_response_for_bad_request(PATH_BAD_REQUEST);
//     generate_generic_response(response, BAD_REQUEST);
//   } else {
//     response = create_response(response, request);
//     generate_response(response);
//   }
//   printf("%s\n", response->response_str);
//   printf("=================================\n");
//   free_request(request);
//   free_response(response);
//
//   return 0;
// }
