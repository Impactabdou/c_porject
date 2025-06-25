#include "../include/game_manager.h"
#include <stdio.h>
#include <stdlib.h>

game *create_game_manager(map *m, unsigned int left_limitation, int game_mode) {
  game *gm = malloc(sizeof(game));
  gm->m = m;
  gm->left_limitation = left_limitation;
  gm->game_mode = game_mode;
  return gm;
}

wall *generate_wall(game *gm) {

  if (gm->left_limitation >= gm->m->width) {
    return NULL;
  }

  unsigned int max_gap_length = get_gap_legnth(*gm);

  unsigned int max_x = gm->m->width - STAND_WIDTH;
  unsigned int min_x = gm->left_limitation;

  unsigned int max_y = gm->m->height - max_gap_length;
  unsigned int min_y = max_gap_length;

  unsigned int x = rand() % (max_x - min_x + 1) + min_x;
  unsigned int y = rand() % (max_y - min_y + 1) + min_y;

  point left_top = create_point(x, y);

  unsigned int gap_height =
      rand() % (max_gap_length - MIN_MODE_GAP + 1) + MIN_MODE_GAP;

  return create_wall(gap_height, STAND_WIDTH, left_top);
}

void add_walls_in_game(game *gm, int num_walls) {
  for (int i = 0; i < num_walls; i++) {
    add_wall_in_game(gm);
  }
}

void add_wall_in_game(game *gm) {
  wall *w = generate_wall(gm);

  if (w == NULL) {
    printf("Limitation has touched borders no space is available\n");
    return;
  }

  int added = add_wall_in_map(gm->m, w);
  if (!added) {
    printf("Cannot add more walls, map is full :\ncurr num of walls : %d | max "
           "num of walls : %d\n",
           gm->m->curr_num_walls, gm->m->max_num_walls);
    return;
  }
  gm->left_limitation = w->top_left.x + STAND_WIDTH + WALL_OFFSET;
  printf("\nWall has been added succesfully\n");
  draw_walls(gm->m);
}

unsigned char get_gap_legnth(game gm) {
  if (gm.game_mode == HARD_MODE) {
    return HARD_MODE_GAP;
  }
  if (gm.game_mode == MID_MODE) {
    return MED_MODE_GAP;
  }
  return EASY_MODE_GAP;
}

void start_game(game *g) {}

game *free_game(game *gm) {
  gm->m = free_map(gm->m);
  return NULL;
}
