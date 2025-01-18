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
    out[star] = (Vector2){10000.f, 0.f};
  }
  return out;
}

void destructStars(Vector2* starArr) {
  free(starArr);
}

static bool getPointIsOnScreenScaled(Vector2 point, Vector2 screenDems, Camera2D cam, float scale) {
  Vector2 remFromCam = removeCam(point, cam);
  bool inX = (remFromCam.y < 0 ? -remFromCam.y : remFromCam.y) <= screenDems.x * scale / (2.0f * cam.zoom);
  bool inY = (remFromCam.x < 0 ? -remFromCam.x : remFromCam.x) <= screenDems.y * scale / (2.0f * cam.zoom);
  return inX && inY;
}

void refreshStars(Vector2* starArr, Camera2D camera, bool force) {
  int i = 0;
  bool nforce = !force;
  Vector2 screenDems = {GetScreenWidth(), GetScreenHeight()};
  while(i < starCount) {
    if(!getPointIsOnScreenScaled(starArr[i], screenDems, camera, starReloadDist) || force) {
      Vector2 rand = applyCam(Vector2Scale(getRandomVector2OnScreen(camera), starSpawnDist), camera);
      if(getPointIsOnScreenScaled(rand, screenDems, camera, 1) && nforce) {
        i++;
        continue;
      }
      starArr[i]= rand;
    }
    i++;
  }
}

void drawStars(Vector2* starArr, Camera2D* cam) {
  float offX = roundf(cam->offset.x);
  float offY = roundf(cam->offset.y);
  for(int i = 0; i < starCount; i++) {
    DrawPixel(starArr[i].y + offX, -starArr[i].x + offY, starColour);
  }
}
