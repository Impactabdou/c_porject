#ifndef H_POINT
#define H_POINT

#define EMPTY_FRAME ' '

typedef struct struct_point {
  int x;
  int y;
} point;

point create_point(int x, int y);
void print_point(point p);

#endif // !H_POINT
