#ifndef camera_h
#define camera_h

#include "../libraries/raylib.h"
#include "../libraries/raymath.h"

#define shakeDampening .1

struct shakeCamera {
  Camera2D base;
  float jitterness;
  Vector2 shakeDirection;
  Vector2 target;
};
typedef struct shakeCamera shakeCamera;

void cameraShakeF(shakeCamera* camera);

void applyCameraShake(shakeCamera* camera, float magnitude, float jitterness, float angle);

void refreshCamera(shakeCamera* cam);

#endif
