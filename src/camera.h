#ifndef camera_h
#define camera_h

#include <raylib.h>
#include <raymath.h>

union shakeCamera {
  Camera2D cam;
};
typedef union shakeCamera shakeCamera;

void camearShake(Camera2D* camera, float angle, float magnitude);

#endif
