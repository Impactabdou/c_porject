#include "../include/map.h"
#include <stdio.h>
#include <stdlib.h>

map *create_map(int width, int height, wall **walls, int num_walls) {
  map *m = malloc(sizeof(map));
  m->walls = walls;
  m->width = width;
  m->height = height;
  m->num_walls = num_walls;
  m->frames = malloc(sizeof(char *) * height);
  for (int row = 0; row < height; row++) {
    m->frames[row] = malloc(sizeof(char) * width);
  }
  return m;
}

void draw_walls(map *m) {
  for (int i = 0; i < m->num_walls; i++) {
    for (int row = m->walls[i]->top_left.y; row < m->walls[i]->bottom_right.y;
         row++) {
      for (int col = m->walls[i]->top_left.x; col < m->walls[i]->top_right.x;
           col++) {
        m->frames[row][col] = WALL_FRAME;
      }
    }
  }
}

void *free_map(map *m) {
  for (int i = 0; i < m->num_walls; i++) {
    m->walls[i] = free_wall(m->walls[i]);
  }
  for (unsigned int row = 0; row < m->height; row++) {
    free(m->frames[row]);
  }
  free(m->frames);
  m->frames = NULL;
  free(m->walls);
  m->walls = NULL;
  free(m);
  return NULL;
}

void print_map(map m) {
  for (unsigned int i = 0; i < m.height; i++) {
    for (unsigned int j = 0; j < m.width; j++) {
      printf("%c", m.frames[i][j]);
    }
    printf("\n");
  }
}
