#include "../include/bird.h"
#include <stdio.h>
#include <stdlib.h>

bird *create_bird(point init_pos) {
  bird *b = malloc(sizeof(bird));
  b->pos = init_pos;
  b->direction = DOWN;
  return b;
}

void move_bird(bird *b, int direction, int speed) {
  switch (direction) {
  case DOWN:
    b->pos.y += speed;
    break;
  case UP:
    b->pos.y -= speed;
    break;
  default:
    printf("Unknown bird direction\n");
    return;
  }
}

void *free_bird(bird *b) {
  free(b);
  return NULL;
}
