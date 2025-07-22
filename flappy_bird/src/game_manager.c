#include "../include/game_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

game *create_game_manager(map *m, unsigned int left_limitation, int game_mode) {
  game *gm = malloc(sizeof(game));
  gm->m = m;
  gm->left_limitation = left_limitation;
  gm->game_mode = game_mode;
  gm->score = 0;
  return gm;
}

wall *generate_wall(game *gm, int ignore_limitation) {

  if (gm->left_limitation >= gm->m->width && !ignore_limitation) {
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

void add_walls_in_game(game *gm, unsigned int num_walls) {
  for (unsigned int i = 0; i < num_walls; i++) {
    add_wall_in_game(gm);
  }
}

void respawn_walls_in_game(game *gm) {
  for (unsigned int wall_id = 0; wall_id < gm->m->curr_num_walls; wall_id++) {
    wall *curr_w = gm->m->walls[wall_id];
    if (out_of_bound_wall(*curr_w)) {
      draw_walls(gm->m, 1);
      curr_w = free_wall(curr_w);
      curr_w = generate_wall(gm, 1);
      reset_wall(curr_w, gm->m->width);
    }
  }
}

void add_wall_in_game(game *gm) {

  wall *w = generate_wall(gm, 0);

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
}

void move_walls(game *gm, unsigned int steps) {
  draw_walls(gm->m, 1);
  for (unsigned int i = 0; i < gm->m->curr_num_walls; i++) {
    move_left(gm->m->walls[i], steps);
  }
}

/**
 * @brief bird moves x ups and x downs simulating a hop like move
 * @caution frame needs to bo updated throught out these moves WALLS MOVE ALONG
 */
int move_bird_in_game(game *gm, int speed, int move_activated) {
  respawn_walls_in_game(gm);
  if (move_activated == 1) {
    unsigned int max_steps = 10;
    for (unsigned int steps = 0; steps <= max_steps; steps++) {
      draw_bird(gm->m, 1);
      move_bird(gm->m->b, UP, speed);
      if (colided(gm, gm->m->b->pos)) {
        return 0;
      }
      move_walls(gm, speed);
      count_score(gm);
      update_frames(gm->m);
      print_map(*gm->m, get_score_string(*gm));
    }
  } else {
    draw_bird(gm->m, 1);
    move_bird(gm->m->b, DOWN, speed);
    if (colided(gm, gm->m->b->pos)) {
      return 0;
    }
    move_walls(gm, speed);
    count_score(gm);
    update_frames(gm->m);
    print_map(*gm->m, get_score_string(*gm));
  }
  return 1;
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

int colided(game *gm, point pos) {
  return !in_range(pos.x, pos.y, *gm->m) ||
         gm->m->frames[pos.y][pos.x] == WALL_FRAME;
}

void count_score(game *gm) {
  for (unsigned int wall_id = 0; wall_id < gm->m->curr_num_walls; wall_id++) {
    if (gm->m->b->pos.x ==
        (gm->m->walls[wall_id]->top_left.x + gm->m->walls[wall_id]->width)) {
      gm->score++;
    }
  }
}

char *get_score_string(game gm) {
  int max_len = 18;
  char *score = malloc(sizeof(char) * max_len);
  sprintf(score, "    score : %d", gm.score);
  int i = strlen(score);
  while (i < max_len) {
    score[i++] = EMPTY_FRAME;
  }
  return score;
}

game *free_game(game *gm) {
  gm->m = free_map(gm->m);
  return NULL;
}
