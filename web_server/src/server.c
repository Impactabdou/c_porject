#include "../include/server.h"
#include "./http/include/http_response.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

server create_server(int service, int port, int domain, int protocol,
                     int backlog, unsigned long interface,
                     void (*lunch)(server s)) {

  server s;
  s.port = port;
  s.service = service;
  s.protocol = protocol;
  s.domain = domain;
  s.backlog = backlog;
  s.lunch = lunch;
  s.interface = interface;

  s.address.sin_family = domain;
  s.address.sin_port = htons(port);
  s.address.sin_addr.s_addr = htonl(interface);

  s.socket = socket(domain, service, protocol);

  if (s.socket == 0) {
    perror("Failed to connect to socket\n");
    exit(1);
  }

  if (bind(s.socket, (struct sockaddr *)&s.address, sizeof(s.address)) < 0) {
    perror("Failed to bind with socket\n");
    exit(1);
  }

  if (listen(s.socket, s.backlog) < 0) {
    perror("Failed to start listening\n");
    exit(1);
  }

  return s;
}

void lunch(server s) {
  while (1) {
    // int client_socket = accept(s.socket, NULL, NULL);
    // if (client_socket == 0) {
    //   perror("Failled to accept client's connection\n");
    //   continue;
    // }
    // char request[MAX_LEN] = {0};
    // http_request http_request;
    // header h;
    // http_data data;
    // http_response http_response;
    //
    // //read(client_socket, request, sizeof(request));
    // printf("%s\n", request);
    // printf("=================================\n");
    // create_request(&http_request, &h, &data, request);
    // create_response(&http_response, &http_request);
    // // generate_response(http_response);
    // free_request(&http_request);
    // free_response(&http_response);
    // printf("=================================\n");
    //
    // close(client_socket);
  }
  close(s.socket);
}
