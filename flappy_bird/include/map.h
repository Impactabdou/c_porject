#ifndef H_MAP
#define H_MAP

#include "bird.h"
#include "wall.h"

typedef struct struct_map {
  char **frames;
  unsigned int width;
  unsigned int height;
  bird *b;
  wall **walls;
  unsigned int max_num_walls;
  unsigned int curr_num_walls;
} map;
map *create_map(unsigned int width, unsigned int height, bird *b,
                unsigned int max_num_walls);
void print_map(map m);
void *free_map(map *m);
void draw_walls(map *m);
void refrech(map *m, wall **walls);
int add_wall_in_map(map *m, wall *w);

#endif // !H_MAP
