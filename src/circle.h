#ifndef circle_h
#define circle_h

#include <raylib.h>

struct circle {
  Vector2 position;
  float radius;
  Color colour;
};
typedef struct circle circle;

void drawCircle(circle*);

#endif
