#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 2048

int main() {

  FILE *html_data;
  int port = 5000;
  int max_req = 20;
  html_data = fopen("./data/index.html", "r");
  if (html_data == NULL) {
    printf("Can't read file\n");
    exit(1);
  }
  char response_data[1024];
  fgets(response_data, 1024, html_data);

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";

  strcat(http_header, response_data);

  // Creating socket

  int server_socket;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    printf("Can't bind with socket\n");
    exit(1);
  }

  if (listen(server_socket, max_req) < 0) {
    printf("Can't listen\n");
    exit(1);
  }

  // Handling client

  int client_sock;
  while (1) {
    printf("waiting for connection\n");
    client_sock = accept(server_socket, NULL, NULL);
    send(client_sock, http_header, sizeof(http_header), 0);
    close(client_sock);
  }

  return 0;
}
