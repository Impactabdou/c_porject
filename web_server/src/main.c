#include "../include/server.h"
#include "./http/include/http_response.h"
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
    header h;
    http_data data;
    http_request http_request;
    http_response http_response;
    char response_str[MAX_LEN] = {0};
    char request[MAX_LEN] = {0};
    read(client_socket, request, sizeof(request));
    printf("%s\n", request);
    printf("=================================\n");
    create_request(&http_request, &h, &data, request);
    print_header(h);
    create_response(&http_response, &http_request);
    generate_response(&http_response, response_str);
    printf("%s\n", response_str);
    send(client_socket, response_str, strlen(response_str), 0);
    printf("=================================\n");
    close(client_socket);
  }
  close(s.socket);
}
