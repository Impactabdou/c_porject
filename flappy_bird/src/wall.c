#include "../include/wall.h"
#include <stdio.h>
#include <stdlib.h>

wall *create_wall(point top_left, point top_right, point bottom_left,
                  point bottom_right) {
  wall *w = malloc(sizeof(wall));
  w->bottom_left = bottom_left;
  w->bottom_right = bottom_right;
  w->top_left = top_left;
  w->top_right = top_right;
  return w;
}

wall **generate_walls(unsigned int num_walls, unsigned int height,
                      unsigned int width) {

  if (num_walls < 2 || num_walls % 2) {
    printf("Number of walls needs to be > 1 and even...\n");
    return NULL;
  }

  wall **walls = malloc(sizeof(wall *) * num_walls);

  int min_wall_gap = 2;
  unsigned int wall_width = 4;
  unsigned int min_space_between_wall = 5;
  unsigned int last_end_x = 0;

  unsigned int min_height = height / 3.5;
  unsigned int max_height = height / 2 - min_wall_gap;
  unsigned int max_space_between_wall = width / 2;

  for (unsigned int i = 0; i < num_walls; i += 2) {
    unsigned int rand_height =
        min_height + rand() % (max_height - min_height + 1);
    unsigned int min_x = last_end_x + min_space_between_wall;
    unsigned int max_x = last_end_x + max_space_between_wall;
    unsigned int start_x = min_x + rand() % (max_x - min_x + 1);
    unsigned int end_x = start_x + wall_width;
    last_end_x = end_x;
    point top_left = {start_x, 0};
    point top_right = {end_x, 0};
    point bottom_left = {start_x, rand_height};
    point bottom_right = {end_x, rand_height};
    walls[i] = create_wall(top_left, top_right, bottom_left, bottom_right);
    unsigned int end_y = height - rand_height;
    point top_left_rv = {start_x, end_y};
    point top_right_rv = {end_x, end_y};
    point bottom_left_rv = {start_x, height};
    point bottom_right_rv = {end_x, height};
    walls[i + 1] =
        create_wall(top_left_rv, top_right_rv, bottom_left_rv, bottom_right_rv);
  }
  return walls;
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
  printf("top_left : \n");
  print_point(w.top_left);
  printf("top_right : \n");
  print_point(w.top_right);
  printf("bottom_left: \n");
  print_point(w.bottom_left);
  printf("bottom_right : \n");
  print_point(w.bottom_right);
}
