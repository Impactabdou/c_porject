#include "../include/map.h"
#include <stdio.h>

int main(int argv, char **argc) {

  unsigned int height = 30;
  unsigned int width = 100;
  unsigned int num_walls = 4;

  wall **walls = generate_walls(num_walls, height, width);

  if (walls == NULL) {
    printf("Critical : No walls\n");
    return -1;
  }

  map *m = create_map(width, height, walls, num_walls);

  draw_walls(m);

  print_map(*m);

  free_map(m);

  // walls = free_walls(walls, num_walls); seg fault here

  return 0;
}
