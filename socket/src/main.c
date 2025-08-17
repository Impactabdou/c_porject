#include "../include/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void lunch(server *s) {

  char buffer[3000];

  printf("========== WAITING FOR CONNECTION ==========");
  int new_socket = accept(s->socket, (struct sockaddr *)&s->address,
                          (socklen_t *)sizeof(s->address));

  read(new_socket, buffer, 3000);
  printf("%s\n", buffer);

  char *hello =
      "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: "
      "Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 "
      "GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: "
      "Closed\n<html><body><h1>Homo Deus</h1></body></html>";

  write(new_socket, hello, strlen(hello));
  close(new_socket);
}

int main() {

  server s =
      server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, lunch);
  s.lunch(&s);

  return 0;
}
