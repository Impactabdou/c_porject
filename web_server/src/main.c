#include "../include/parser.h"
#include "../include/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void lunch(server s);

int main() {
  /*int service = SOCK_STREAM;
  int port = 8080;
  int domain = AF_INET;
  int protocol = 0;
  int backlog = 5;
  unsigned long interface = INADDR_ANY;

  server s =
      create_server(service, port, domain, protocol, backlog, interface, lunch);

  s.lunch(s);*/

  header *h = NULL;

  const char request[MAX_LEN] =
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

  create_header(h, request);

  free(h);

  return 0;
}

void lunch(server s) {
  while (1) {
    int client_socket = accept(s.socket, NULL, NULL);
    if (client_socket == 0) {
      perror("Failled to accept client's connection\n");
      continue;
    }
    char buffer[2048] = {0};
    char response[8192] = {0};
    int len = read(client_socket, buffer, sizeof(buffer));
    printf("Client respons : %s\n", buffer);
    close(client_socket);
  }
  close(s.socket);
}
