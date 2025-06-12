#ifndef H_WALL
#define H_WALL
#include "point.h"

#define WALL_FRAME 'x'

typedef struct struct_wall {
  point top_left;
  point bottom_left;
  point top_right;
  point bottom_right;
} wall;

wall *create_wall(point top_left, point top_right, point bottom_left,
                  point bottom_right);

void *free_wall(wall *w);

void print_wall(wall w);

#endif // !H_WALL
