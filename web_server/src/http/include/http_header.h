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
  5 /* this will change thorught when ever more feilds are added to the header \
     */

/* HTTP response status*/
#define CODE_OK 200
#define BAD_REQUEST 400
#define UNAUTHORIZED 401
#define FORBIDDEN 403
#define NOT_FOUND 404
#define INTERNAL_SERVER_EROOR 500

typedef struct http_request_header {
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
} http_request_header;

typedef struct http_response_header {
  char http_version[MAX_LEN_PARAM];
  char response_status[MAX_LEN_PARAM];
  char date[MAX_LEN_PARAM];
  char content_type[MAX_LEN_PARAM];
  char header_str[MAX_LEN];
} http_response_header;

http_request_header *create_request_header(http_request_header *h,
                                           const char request[MAX_LEN]);

void set_request_header(http_request_header *h, char request_header[MAX_LEN]);

int parse_request_header_params(const char header[MAX_LEN_PARAM],
                                const char key[MAX_LEN_PARAM],
                                char value[MAX_LEN_PARAM]);

void set_methode(http_request_header *h,
                 const char request_header[MAX_LEN_PARAM]);

void print_request_header(http_request_header header);

void free_request_header(http_request_header *header);

/* HTTP response header */
http_response_header *
create_response_header(http_response_header *response_header,
                       http_request_header request_header);

void generate_date(char buffer[MAX_LEN_PARAM]);

void set_header_response(http_response_header *response_header,
                         const char *methode);

void to_string_response_header(http_response_header *response_header);

void sanitise_header_fields(const char sanitised_header[MAX_LEN],
                            char sanitised_header_fields[MAX_LEN]);

void free_http_response_header(http_response_header *header);

#endif // !H_HEADER
