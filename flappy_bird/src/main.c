#include "../include/map.h"
#include <stdlib.h>
int main(int argv, char **argc) {

  point top_l = {0, 0};
  point top_r = {3, 0};
  point bottom_l = {0, 3};
  point bottom_r = {3, 3};

  wall *w = create_wall(top_l, top_r, bottom_l, bottom_r);

  wall **walls = malloc(sizeof(wall *) * 1);

  walls[0] = w;

  map *m = create_map(30, 20, walls, 1);

  draw_walls(m);

  print_map(*m);

  return 0;
}
