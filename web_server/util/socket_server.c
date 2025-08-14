#include <netinet/in.h> /* add struct*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LEN 1024

int main() {
  int sock;
  int port = 5000;
  int max_req = 20;
  /*sock func takes :
  doamin = where the socket will opperate (ie THE INTERNET)
  type = stream is TCP and datagrame is UDP
  protocal = the number of each protocol can be found in /etc/services (ie 0
  for TCP)*/
  sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;         /* general type of addresse v4 or v6*/
  addr.sin_addr.s_addr = INADDR_ANY; /* network addresse (ie local machine ip)*/
  addr.sin_port = htons(port);       /* conversion si obliged*/

  /* bind func
   cast to sockaddr to make sure it's the right struct addr*/
  bind(sock, (struct sockaddr *)&addr, sizeof(addr));

  listen(sock, max_req);

  int connection;
  char buffer[MAX_LEN] = {0};

  /*accept fun
  struct sockaddr addr is the second parametor and tells us where the
  connection is comming from third param is the size of struct*/
  connection = accept(sock, NULL, NULL);

  /* read from the connection
   put the data sent from the client to the buffer*/
  read(connection, buffer, MAX_LEN);

  printf("Client send this :\n%s\n", buffer);

  return 0;
}
