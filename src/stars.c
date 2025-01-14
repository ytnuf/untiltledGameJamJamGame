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

Vector2* initStars(int star) {
  Vector2* out = (Vector2*)malloc(sizeof(Vector2) * star);
  while(star-- > 0) {
    out[star] = (Vector2){10000, 10000};
  }
  return out;
}

void destructStars(Vector2* starArr) {
  free(starArr);
}

bool getPointIsOnScreenScaled(Vector2 point, Camera2D cam, float scale) {
  Vector2 remFromCam = removeCam(point, cam);
  bool inX = absf(remFromCam.y) <= GetScreenWidth() * scale / (2.0f * cam.zoom);
  bool inY = absf(remFromCam.x) <= GetScreenHeight() * scale / (2.0f * cam.zoom);
  return inX && inY;
}

void refreshStars(Vector2* starArr, Camera2D Camera, bool force) {
  int i = 0;
  while(i < starCount) {
    if(!getPointIsOnScreenScaled(starArr[i], Camera, starReloadDist) || force) {
      Vector2 rand = applyCam(Vector2Scale(getRandomVector2OnScreen(Camera), starSpawnDist), Camera);
      if(getPointIsOnScreenScaled(rand, Camera, 1) && !force)
        continue;
      starArr[i] = rand;
    }
    i++;
  }
}

void drawStars(Vector2* starArr) {
  for(int i = 0; i < starCount; i++)
    drawCircle(&(circle){starArr[i], starRadius, starColour});
}
