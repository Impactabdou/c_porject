#ifndef H_PARSER
#define H_PARSER
#include <stdbool.h>
#define MAX_LEN 8000
#define MAX_LEN_PARAM 200

typedef struct header {
  char accept[MAX_LEN_PARAM];
  char accept_charset[MAX_LEN_PARAM];
  char accept_datetime[MAX_LEN_PARAM];
  char accept_encoding[MAX_LEN_PARAM];
  char accept_language[MAX_LEN_PARAM];
  char user_agent[MAX_LEN_PARAM];
  char authorized[MAX_LEN_PARAM];
  char content_type[MAX_LEN_PARAM];
  char cookie[MAX_LEN_PARAM];
  char host[MAX_LEN_PARAM];
  bool sec_g;
  char connections[MAX_LEN_PARAM];
  bool upgrade_insecure_requests;
} header;

typedef struct parser {
  header h;
  char data[8000];
} parser;

void create_header(header *h, const char request[MAX_LEN]);

void parse_header(header *h, char request_header[MAX_LEN]);

int parse_key(const char string[MAX_LEN_PARAM], const char key[MAX_LEN_PARAM],
              char value[MAX_LEN_PARAM]);

#endif
