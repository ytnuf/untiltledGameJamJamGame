#include "stars.h"
#include "circle.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define starDist 1.01
#define starSpawnDist 1.1
#define starReloadDist 1.1

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
  Vector2 remFromCam = Vector2Add(Vector2Subtract(point, (Vector2){-cam.target.y, cam.target.x}), (Vector2){-cam.offset.y, cam.offset.x});
  bool inX = abs(remFromCam.y) < GetScreenWidth() * scale / 2.0f;
  bool inY = abs(remFromCam.x) < GetScreenHeight() * scale / 2.0f;
  return inX && inY;
}

void refreshStars(circle* starArr, Camera2D Camera) {
  for(int i = 0; i < starCount; i++)
    if(!getPointIsOnScreenScaled(starArr[i].position, Camera, starReloadDist)) {
      Vector2 rand = Vector2Scale(getRandomVector2OnScreen(Camera), starSpawnDist);
      while(getPointIsOnScreenScaled(rand, Camera, 1)) {
        rand = Vector2Scale(getRandomVector2OnScreen(Camera), starSpawnDist);
        if(!getPointIsOnScreenScaled(rand, Camera, starSpawnDist))
          starArr[i].position = rand;
      }
    }
}
