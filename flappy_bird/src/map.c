#include "../include/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

map *create_map(unsigned int width, unsigned int height, bird *b,
                unsigned int max_num_walls) {
  map *m = malloc(sizeof(map));
  m->b = b;
  m->walls = (wall **)malloc(sizeof(wall *) * max_num_walls);
  m->width = width;
  m->height = height;
  m->max_num_walls = max_num_walls;
  m->frames = malloc(sizeof(char *) * height);
  for (unsigned int row = 0; row < height; row++) {
    m->frames[row] = malloc(sizeof(char) * width);
  }
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      m->frames[i][j] = EMPTY_FRAME;
    }
  }
  return m;
}

int add_wall_in_map(map *m, wall *w) {
  if (m->curr_num_walls >= m->max_num_walls) {
    return 0;
  }
  m->walls[m->curr_num_walls++] = w;
  return 1;
}

int in_range(unsigned int x, unsigned int y, map m) {
  return x < m.width && y < m.height;
}

void update_frames(map *m) {
  draw_walls(m, 0);
  draw_bird(m, 0);
}

void draw_bird(map *m, int reset) {
  bird *b = m->b;
  if (!in_range(b->pos.x, b->pos.y, *m)) {
    printf("Bird OUT OF RANGE\n");
    return;
  }
  if (reset) {
    m->frames[b->pos.y][b->pos.x] = EMPTY_FRAME;
  } else {
    m->frames[b->pos.y][b->pos.x] = BIRD_FRAME;
  }
}

void draw_walls(map *m, int reset) {
  for (unsigned int curr_wall = 0; curr_wall < m->curr_num_walls; curr_wall++) {

    point *curr_wall_cords = get_wall_cords(*m->walls[curr_wall]);
    unsigned int col_start = curr_wall_cords[TOP_L].x;
    unsigned int col_end = curr_wall_cords[TOP_R].x;
    unsigned int row_empty_start = curr_wall_cords[TOP_L].y;
    unsigned int row_empty_end = curr_wall_cords[BOTTOM_L].y;
    free(curr_wall_cords);
    for (unsigned int row = 0; row < m->height; row++) {
      if (row >= row_empty_start && row < row_empty_end) {
        continue;
      }
      for (unsigned int col = col_start; col < col_end; col++) {
        if (!in_range(col, row, *m)) {
          continue;
        }
        if (reset) {
          m->frames[row][col] = EMPTY_FRAME;
        } else {

          m->frames[row][col] = WALL_FRAME;
        }
      }
    }
  }
}

void *free_map(map *m) {
  m->b = free_bird(m->b);
  for (unsigned int i = 0; i < m->curr_num_walls; i++) {
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
  usleep(30000);
  system("clear");
  char *border_str = (char *)malloc(sizeof(char) * m.width + 1);

  for (unsigned int row = 0; row < m.width; row++) {
    border_str[row] = '#';
  }
  border_str[m.width] = '\0';
  printf("%s\n", border_str);

  for (unsigned int i = 0; i < m.height; i++) {
    printf("#");
    for (unsigned int j = 0; j < m.width; j++) {
      printf("%c", m.frames[i][j]);
    }
    printf("#\n");
  }
  printf("%s\n", border_str);
}
