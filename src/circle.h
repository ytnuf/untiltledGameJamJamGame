#ifndef circle_h
#define circle_h

#include "../libraries/raylib.h"

struct circle {
  Vector2 position;
  float radius;
  Color colour;
};
typedef struct circle circle;

void drawCircle(circle*, Vector2 screenDimensions);

circle randomCircleOnScreen(Camera2D cam, Color col, float maxSize, float minSize);

Vector2 getRandomVector2OnScreen(Camera2D cam);

Vector2 removeCam(Vector2 v, Camera2D cam);

Vector2 applyCam(Vector2 v, Camera2D cam);

float randSingle();

#endif
