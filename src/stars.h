#ifndef stars_h
#define stars_h

#include <raylib.h>
#include "circle.h"

#define starCount 1600
#define starColour WHITE

circle* initStars(int stars);

void destructStars(circle* starArr);

void refreshStars(circle* starArr, Camera2D Camera);

#endif
