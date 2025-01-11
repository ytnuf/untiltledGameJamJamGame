#include "stars.h"
#include "circle.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

circle* initStars(int star) {
  circle* out = (circle*)malloc(sizeof(circle) * star);
  while(star-- > 0) {
    out[star] = (circle){Vector2Zero(), 1, starColour};
  }
  return out;
}

void destructStars(circle* starArr) {
  free(starArr);
}

bool getPointIsOnScreen(Vector2 point, Camera2D cam) {
  Vector2 remFromCam = Vector2Add(Vector2Subtract(point, (Vector2){-cam.target.y, cam.target.x}), (Vector2){-cam.offset.y, cam.offset.x});
  bool inX = abs(remFromCam.y) < GetScreenWidth() / 2.0f;
  bool inY = abs(remFromCam.x) < GetScreenHeight() / 2.0f;
  return inX && inY;
}

void refreshStars(circle* starArr, Camera2D Camera) {
  for(int i = 0; i < starCount; i++)
    if(!getPointIsOnScreen(starArr[i].position, Camera))
      starArr[i].position = getRandomVector2OnScreen(Camera);
}
