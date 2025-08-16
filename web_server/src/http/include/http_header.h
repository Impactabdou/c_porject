#ifndef H_HEADER
#define H_HEADER
#include "../../../include/shared.h"
#include <stdbool.h>
#include <stdlib.h>

/* header macros */
#define ACCEPT "Accept\0"
#define ACCEPT_ENCODING "Accept-Encoding\0"
#define ACCEPT_LANG "Accept-Language\0"
#define HOST "Host\0"
#define CONNECTION "Connection\0"
#define USER_AGENT "User-Agent\0"
#define HEADER_DEFAULT_NUMBER_PARAMS                                           \
  6 /* this will change thorught when ever more feilds are added to the header \
     */

typedef struct header {
  char methode[MAX_LEN_PARAM];
  char http_version[MAX_LEN_PARAM];
  char path[MAX_LEN_PARAM];
  char http_flag[MAX_LEN_PARAM];
  char accept[MAX_LEN_PARAM];
  char accept_encoding[MAX_LEN_PARAM];
  char accept_language[MAX_LEN_PARAM];
  char user_agent[MAX_LEN_PARAM];
  char host[MAX_LEN_PARAM];
  char connection[MAX_LEN_PARAM];
  size_t number_params;
} header;

void create_header(header *h, const char request[MAX_LEN]);

void set_header(header *h, char request_header[MAX_LEN]);

int parse_header_params(const char header[MAX_LEN_PARAM],
                        const char key[MAX_LEN_PARAM],
                        char value[MAX_LEN_PARAM]);

void set_methode(header *h, const char request_header[MAX_LEN_PARAM]);

void print_header(header h);

void free_header(header *h);

#endif // !H_HEADER
