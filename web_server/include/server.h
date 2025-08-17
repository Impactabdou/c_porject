#ifndef H_SERV
#define H_SERV

#define GET 0
#define PATH_MAX 1024

/* Request status */
#define OK 200
#define BAD_REQUEST 400
#define UNAUTHORIZED 401
#define FORBIDDEN 403
#define NOT_FOUND 404

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

int get_html_data(char *path, char *data_str);

void extract_chars_from(char *src, char *dest, char stop);
void handle_request(char *request, char *response);
void format_http_header(char *repsonse, int server);

#endif // !H_SERV
