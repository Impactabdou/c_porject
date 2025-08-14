#include "../include/debug.h"
#include <stdio.h>
#include <stdlib.h>

void debug_print(const char *msg) {
  fprintf(stderr, "msg : %s\n", msg);
  exit(1);
}
