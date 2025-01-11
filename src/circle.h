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

circle randomCircleOnScreen(Camera2D cam, Color col, float maxSize, float minSize);

Vector2 getRandomVector2OnScreen(Camera2D cam);

#endif
