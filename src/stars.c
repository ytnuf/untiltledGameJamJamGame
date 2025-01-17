#include "stars.h"
#include "circle.h"
#include "include.h"
#include <stdlib.h>

#define starDist 1.01
#define starSpawnDist 1.3
#define starReloadDist 1.4
#define randomnessResolution 2

Vector2* initStars(int star) {
  Vector2* out = (Vector2*)malloc(sizeof(Vector2) * star);
  while(star-- > 0) {
    out[star] = (Vector2){10000};
  }
  return out;
}

void destructStars(Vector2* starArr) {
  free(starArr);
}

bool getPointIsOnScreenScaled(Vector2 point, Vector2 screenDems, Camera2D cam, float scale) {
  Vector2 remFromCam = removeCam(point, cam);
  bool inX = (remFromCam.y < 0 ? -remFromCam.y : remFromCam.y) <= screenDems.x * scale / (2.0f * cam.zoom);
  bool inY = (remFromCam.x < 0 ? -remFromCam.x : remFromCam.x) <= screenDems.y * scale / (2.0f * cam.zoom);
  return inX && inY;
}

void refreshStars(Vector2* starArr, Camera2D Camera, bool force) {
  int i = 0;
  bool nforce = !force;
  Vector2 screenDems = {GetScreenWidth(), GetScreenHeight()};
  while(i < starCount) {
    if(!getPointIsOnScreenScaled(starArr[i], screenDems, Camera, starReloadDist) || force) {
      Vector2 rand = applyCam(Vector2Scale(getRandomVector2OnScreen(Camera), starSpawnDist), Camera);
      if(getPointIsOnScreenScaled(rand, screenDems, Camera, 1) && nforce) {
        i++;
        continue;
      }
      starArr[i]= rand;
    }
    i++;
  }
}

void drawStars(Vector2* starArr, Camera2D* cam) {
  Vector2 screenDems = {GetScreenWidth(), GetScreenHeight()};
  circle tmp = {{0}, 1, starColour};
  for(int i = 0; i < starCount; i++) {
    tmp.position = starArr[i];
    drawCircle(&tmp, screenDems);
  }
}
