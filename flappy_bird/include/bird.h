#ifndef H_BIRD
#define H_BIRD
#include "point.h"

#define UP 1
#define DOWN 0
#define STATIC -1
#define BIRD_FRAME '@'

typedef struct bird_struct {
  point pos;
  int direction; // up or down
} bird;

bird *create_bird(point init_pos);

void move_bird(bird *b, int direction, int speed);

void *free_bird(bird *b);

#endif // !H_BIRD
