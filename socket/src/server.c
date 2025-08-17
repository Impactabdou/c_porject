#include "../include/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

server server_constructor(int domain, int protocal, int service,
                          unsigned long interface, int port, int backlog,
                          void (*lunch)(struct t_server *s)) {
  server s;
  s.domain = domain;
  s.backlog = backlog;
  s.interface = interface;
  s.port = port;
  s.service = service;
  s.protocal = protocal;

  s.address.sin_family = domain;
  s.address.sin_port = htons(port);
  s.address.sin_addr.s_addr = htonl(interface);

  s.socket = socket(domain, service, protocal);

  if (s.socket == 0) {
    perror("Failed to connect to socket...\n");
    exit(1); // Failure
  }

  if (bind(s.socket, (struct sockaddr *)&s.address, sizeof(s.address)) < 0) {
    perror("Failed to bind socket...\n");
    exit(1); // Failure
  }

  if (listen(s.socket, s.backlog) < 0) {
    perror("Failed listen...\n");
    exit(1);
  }

  s.lunch = lunch;

  return s;
}
