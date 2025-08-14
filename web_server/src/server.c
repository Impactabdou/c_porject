#include "../include/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*void extract_chars_from(char *src, char *dest, char stop) {
  size_t i = 0;
  while (src[i] != stop && i < strlen(src)) {
    dest[i] = src[i];
    i++;
  }
}

void handle_request(char *request, char *response) {
  char path[1024] = {0};
  char stop = 32;

  if (strncmp(request, "GET", 3) == 0) {
    request += 4;
    extract_chars_from(request, path, stop);
    int status = get_html_data(path, response);
    format_http_header(response, status);
    return;
  }
  printf("Request not handled for now\n");
}

void get_file(char *path) {
  if (!path || path[0] != '/' || strlen(path) > PATH_MAX) {
    path = NULL;
    return;
  }

  char full_path[PATH_MAX * 2];

  snprintf(full_path, sizeof(full_path), "./public%s", path);

  strncpy(path, full_path, PATH_MAX);
}

int get_html_data(char *path, char *data_str) {

  get_file(path);

  if (path == NULL) {
    printf("Wrong path\n");
    return BAD_REQUEST;
  }

  FILE *html_data = fopen(path, "r");

  if (html_data == NULL) {
    perror("Error while loading file ");
    data_str = NULL;
    return NOT_FOUND;
  }

  char buffer[200];

  while (fgets(buffer, 200, html_data) != NULL) {
    strncat(data_str, buffer, 200);
  }
  return OK;
}

void format_http_header(char *response, int status) {

  char *header;

  if (status == OK) {
    header = "HTTP/1.1 200\r\n";
  } else {
    header = "HTTP/1.1 400\r\n";
  }

  strncat(response, header, sizeof(response) - strlen(response) - 1);
}*/
