#ifndef H_SHARED
#define H_SHARED

/* size macros */
#define MAX_LEN 8000
#define DATA_LEN 10000
#define RESPONSE_LEN DATA_LEN + MAX_LEN
#define MAX_LEN_PARAM 200
#define MAX_LINE 1024

/* HTTP methodes */
#define GET "GET"
#define POST "POST"

/* Generic paths */
#define PATH_BAD_REQUEST "./public/400.html"
#define PATH_NOT_FOUND "./public/404.html"

void sanitise_input(const char *input, char *output);

#endif // !H_SHARED
