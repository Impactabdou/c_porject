#include "../include/server.h"
#include "./http/include/http_response.h"
#include "http/include/http_request.h"
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void lunch(server s);

int main() {
  int service = SOCK_STREAM;
  int port = 8080;
  int domain = AF_INET;
  int protocol = 0;
  int backlog = 5;
  unsigned long interface = INADDR_ANY;

  server s =
      create_server(service, port, domain, protocol, backlog, interface, lunch);

  s.lunch(s);

  return 0;
}

void lunch(server s) {
  while (1) {
    printf("Waiting for connection\n");
    int client_socket = accept(s.socket, NULL, NULL);
    if (client_socket == 0) {
      perror("Failled to accept client's connection\n");
      continue;
    }
    char buffer[MAX_LEN] = {0};
    size_t len = read(client_socket, buffer, sizeof(buffer));
    if (len == 0) {
      perror("len is null ");
      break;
    }
    http_request *request = NULL;
    http_response *response = NULL;
    printf("%s\n", buffer);
    printf("=================================\n");
    request = create_request(request, buffer);
    print_request_header(*request->h);
    response = create_response(response, request);
    generate_response(response);
    printf("%s\n", response->response_str);
    send(client_socket, response->response_str, strlen(response->response_str),
         0);
    printf("=================================\n");
    free_request(request);
    free_response(response);
    close(client_socket);
  }
  close(s.socket);
}
