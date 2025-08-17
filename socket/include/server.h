#ifndef H_SERVER
#define H_SERVER
#include <netinet/in.h>
#include <sys/socket.h>
typedef struct t_server {
  int domain;
  int protocal;
  int service;
  unsigned long interface;
  int port;
  int backlog;
  int socket;

  struct sockaddr_in address;

  void (*lunch)(struct t_server *);

} server;

server server_constructor(int domain, int protocal, int service,
                          unsigned long interface, int port, int backlog,
                          void (*lunch)(server *s));

#endif
