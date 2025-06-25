#include "../include/bird.h"
#include <stdlib.h>

bird *create_bird(point init_pos) {
  bird *b = malloc(sizeof(bird));
  b->pos = init_pos;
  b->direction = DOWN;
  return b;
}

void *free_bird(bird *b) {
  free(b);
  return NULL;
}
