#ifndef H_BIRD
#define H_BIRD
#include "point.h"

typedef struct bird_struct {
  point pos;
  int direction; // up or down
} bird;

#endif // !H_BIRD
