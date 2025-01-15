#ifndef stars_h
#define stars_h

#include <raylib.h>
#include "circle.h"

#define starCount 150
#define starColour WHITE
#define starRadius 1

Vector2* initStars(int stars);

void destructStars(Vector2* starArr);

void refreshStars(Vector2* starArr, Camera2D Camera, bool force);

void drawStars(Vector2* starArr, Camera2D* cam);

#endif
