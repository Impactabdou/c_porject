#include "../include/point.h"
#include <stdio.h>

point create_point(int x, int y) {
  point p = {x, y};
  return p;
}

void print_point(point p) { printf("x : %d | y : %d\n", p.x, p.y); }
