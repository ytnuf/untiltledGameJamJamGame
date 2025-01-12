#include "stars.h"
#include "circle.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define starDist 1.01
#define starSpawnDist 1.3
#define starReloadDist 1.4
#define randomnessResolution 2

float absf(float x) {
  return x < 0 ? -x : x;
}

circle* initStars(int star) {
  circle* out = (circle*)malloc(sizeof(circle) * star);
  while(star-- > 0) {
    out[star] = (circle){(Vector2){10000, 10000}, 1, starColour};
  }
  return out;
}

void destructStars(circle* starArr) {
  free(starArr);
}

bool getPointIsOnScreenScaled(Vector2 point, Camera2D cam, float scale) {
  Vector2 remFromCam = removeCam(point, cam);
  bool inX = absf(remFromCam.y) <= GetScreenWidth() * scale / 2.0f;
  bool inY = absf(remFromCam.x) <= GetScreenHeight() * scale / 2.0f;
  return inX && inY;
}

void refreshStars(circle* starArr, Camera2D Camera, bool force) {
  int i = 0;
  while(i < starCount) {
    if(!getPointIsOnScreenScaled(starArr[i].position, Camera, starReloadDist) || force) {
      Vector2 rand = applyCam(Vector2Scale(getRandomVector2OnScreen(Camera), starSpawnDist), Camera);
      if(getPointIsOnScreenScaled(rand, Camera, 1) && !force)
        continue;
      starArr[i].position = rand;
    }
    i++;
  }
}
