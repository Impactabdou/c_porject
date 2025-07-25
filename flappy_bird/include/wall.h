#ifndef H_WALL
#define H_WALL
#include "point.h"

#define WALL_FRAME 'x'

#define TOP_L 0
#define TOP_R 1
#define BOTTOM_L 2
#define BOTTOM_R 3

#define STAND_WIDTH 3
#define WALL_OFFSET 7

#define EASY_MODE_GAP 15
#define MED_MODE_GAP 13
#define HARD_MODE_GAP 10
#define MIN_MODE_GAP 10

typedef struct struct_wall {
  unsigned int width;
  unsigned int height;
  point top_left;
} wall;

wall *create_wall(unsigned int height, unsigned int width, point top_left);

void *free_wall(wall *w);

void print_wall(wall w);

wall **generate_walls(unsigned int num_walls, unsigned int height,
                      unsigned int width);

void move_left(wall *w, int num_steps);

point *get_wall_cords(wall w);

void *free_walls(wall **w, unsigned int num_walls);

int out_of_bound_wall(wall w);

void reset_wall(wall *w, int width);

#endif // !H_WALL
