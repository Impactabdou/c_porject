#ifndef H_SERV
#define H_SERV

#define PATH_MAX 1024

#include <netinet/in.h>
typedef struct t_server {

  int socket;
  int service;
  int port;
  int domain;
  int protocol;
  int backlog;
  unsigned long interface;

  struct sockaddr_in address;
  void (*lunch)(struct t_server);

} server;

server create_server(int service, int port, int domain, int protocol,
                     int backlog, unsigned long interface,
                     void (*lunch)(server s));

#endif // !H_SERV
