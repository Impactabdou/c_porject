#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Execution must be : %s <ip of host>\n", argv[1]);
    exit(1);
  }

  char *address = argv[1];

  int client_sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_port = htons(80);
  addr.sin_family = AF_INET;
  inet_aton(address, &addr.sin_addr.s_addr);

  connect(client_sock, (struct sockaddr *)&addr, sizeof(addr));

  char request[] = "GET / HTTP/1.1\r\n\r\n";
  char response[2048];

  send(client_sock, request, sizeof(request), 0);

  recv(client_sock, &response, sizeof(response), 0);

  printf("%s", response);

  close(client_sock);

  return 0;
}
