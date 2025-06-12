#ifndef H_MAP
#define H_MAP

#include "wall.h"

typedef struct struct_map {
  char **frames;
  unsigned int width;
  unsigned int height;
  wall **walls;
  unsigned int num_walls;
} map;

void print_map(map m);
void *free_map(map *m);
map *create_map(unsigned int width, unsigned int height, wall **walls,
                unsigned int num_walls);
void draw_walls(map *m);

#endif // !H_MAP
