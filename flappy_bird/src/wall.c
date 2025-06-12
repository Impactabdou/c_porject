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

void *free_wall(wall *w) {
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
