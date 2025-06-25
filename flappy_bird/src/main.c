#include "../include/game_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand((unsigned)time(NULL));

  unsigned int map_width = 150;
  unsigned int map_height = 40;
  unsigned int max_num_walls = 4;
  unsigned int left_limitation = 10;

  point init_pos_bird = {5, map_height / 2};

  bird *b = create_bird(init_pos_bird);

  map *m = create_map(map_width, map_height, b, max_num_walls);

  game *gm = create_game_manager(m, left_limitation, EASY_MODE);

  add_walls_in_game(gm, 1);

  int terst;
  while (1) {
    print_map(*m);

    draw_walls(gm->m);

    move_walls(gm);
  }

  return 0;
}
