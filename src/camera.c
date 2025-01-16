#include "camera.h"
#include "circle.h"
#include "include.h"

float randSingleFull() {
  return (randSingle() - .5f) * 2.0f;
}

Vector2 randVec() {
  return (Vector2){randSingleFull(), randSingleFull()};
}

void cameraShakeF(shakeCamera* camera) {
  Vector2 randV = Vector2Scale(randVec(), camera->jitterness);
  Vector2 end = Vector2Add(randV, camera->target);
  randV = Vector2Scale(randVec(), camera->jitterness);
  camera->shakeDirection = Vector2Add(camera->shakeDirection, randV);
  end = Vector2Add(end, camera->shakeDirection);
  camera->jitterness += -camera->jitterness * shakeDampening;
  camera->shakeDirection = Vector2Subtract(camera->shakeDirection, Vector2Scale(camera->shakeDirection, shakeDampening));
}

void applyCameraShake(shakeCamera* camera, float magnitude, float jitterness, float angle) {
  float prevMag = Vector2Length(camera->shakeDirection);
  float nextMag = magnitude + prevMag;
  Vector2 nextDirection = Vector2Normalize(Vector2Add( Vector2Scale((Vector2){cosf(angle), sinf(angle)}, magnitude), camera->shakeDirection));
  camera->shakeDirection = Vector2Scale(nextDirection, nextMag);
  camera->jitterness += jitterness;
}

void refreshCamera(shakeCamera* camera) {
  camera->base.target = Vector2Add(camera->target, camera->shakeDirection);
}
