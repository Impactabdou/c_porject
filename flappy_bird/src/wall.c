#include "../include/wall.h"
#include <stdio.h>
#include <stdlib.h>

wall *create_wall(unsigned int height, unsigned int width, point top_left) {
  wall *w = malloc(sizeof(wall));
  w->height = height;
  w->width = width;
  w->top_left = top_left;
  return w;
}

void move_left(wall *w, int steps) {
  if (w->top_left.x == 0) {
    return;
  }
  w->top_left.x -= steps;
}

int out_of_bound_wall(wall w) { return w.top_left.x == 0; }

void reset_wall(wall *w, int width) { w->top_left.x = width; }

point *get_wall_cords(wall w) {
  point *cords = malloc(sizeof(point) * 4);
  cords[TOP_L] = w.top_left;
  cords[TOP_R] =
      create_point(w.top_left.x + w.width, w.top_left.y); // top right
  cords[BOTTOM_L] =
      create_point(w.top_left.x, w.top_left.y + w.height); // bottom left
  cords[BOTTOM_R] = create_point(cords[2].x, cords[2].y);  // bottom right
  return cords;
}

void *free_wall(wall *w) {
  free(w);
  return NULL;
}

void *free_walls(wall **w, unsigned int num_walls) {
  for (unsigned int i = 0; i < num_walls; i++) {
    w[i] = free_wall(w[i]);
  }
  free(w);
  return NULL;
}

void print_wall(wall w) {
  printf("width : %d\nHeight : %d\n", w.width, w.height);
  printf("top_left : \n");
  print_point(w.top_left);
}
