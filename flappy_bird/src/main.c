#include "../include/game_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand((unsigned)time(NULL));

  unsigned int map_width = 150;
  unsigned int map_height = 40;
  unsigned int max_num_walls = 4;
  unsigned int left_limitation = 50;
  unsigned int number_of_walls_at_start = 1;
  unsigned int wall_speed = 2;
  int bird_speed = 1;

  point init_pos_bird = {5, map_height / 2};

  bird *b = create_bird(init_pos_bird);

  map *m = create_map(map_width, map_height, b, max_num_walls);

  game *gm = create_game_manager(m, left_limitation, EASY_MODE);

  add_walls_in_game(gm, number_of_walls_at_start);

  unsigned int count = 0;
  unsigned int force_break_game = 200000000;

  /**
   * First game frame
   * */
  print_map(*m);
  count++;

  int move_activated;

  while (1) {
    if (count++ > force_break_game) {
      break;
    }
    printf("1 to jump \n");
    scanf(" %d", &move_activated);
    move_bird_in_game(gm, bird_speed, move_activated);
    move_activated = 0;
  }

  free_game(gm);

  return 0;
}
