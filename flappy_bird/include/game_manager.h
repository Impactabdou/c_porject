#ifndef H_GAME_M
#define H_GAME_M

#define MAX_NUM_WALL_IN_FRAME 3
#define STATIC_WALL 1 // if walls have same widths or not

#define HARD_MODE 0
#define MID_MODE 1
#define EASY_MODE 2

#include "./map.h"

typedef struct game_struct {
  map m;
  wall *walls;
  bird b;
} game;

#endif
