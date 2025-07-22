#ifndef H_GAME_M
#define H_GAME_M

#define MAX_NUM_WALL_IN_FRAME 3
#define STATIC_WALL 1 // if walls have same widths or not

#define HARD_MODE 0
#define MID_MODE 1
#define EASY_MODE 2

#include "./map.h"

typedef struct game_struct {
  map *m;
  unsigned char game_mode;
  unsigned int left_limitation;
} game;

game *create_game_manager(map *m, unsigned int left_limitation, int mode);

game *free_game(game *gm);

void move_walls(game *gm, unsigned int steps);

int move_bird_in_game(game *gm, int speed, int move_activated);

unsigned char get_gap_legnth(game gm);

void add_wall_in_game(game *gm);

void add_walls_in_game(game *gm, int num_walls);

int colided(game *gm, point pos);
#endif
