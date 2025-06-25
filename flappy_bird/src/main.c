#include "../include/game_manager.h"
#include <stdlib.h>
#include <time.h>

int main() {

  srand((unsigned)time(NULL));

  unsigned int map_width = 100;
  unsigned int map_height = 40;
  unsigned int max_num_walls = 4;
  unsigned int left_limitation = 10;

  point init_pos_bird = {5, map_height / 2};

  bird *b = create_bird(init_pos_bird);

  map *m = create_map(map_width, map_height, b, max_num_walls);

  game *gm = create_game_manager(m, left_limitation, EASY_MODE);

  print_map(*m);

  add_walls_in_game(gm, 3);

  print_map(*m);

  return 0;
}
