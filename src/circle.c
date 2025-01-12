#include "circle.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define scalar (Vector2){1, -1}

Vector2 toCartesian(Vector2 v) {
  return (Vector2){-v.y, v.x};
}

void drawCircle(circle* circle) {
  Vector2 windowSize = {GetScreenWidth(), GetScreenHeight()};
  DrawCircle(circle->position.y + (windowSize.x / 2.0f), -circle->position.x + (windowSize.y / 2.0f), circle->radius, circle->colour);
}

//seed before.
float randSingle() {
  return (float)rand() / (float)RAND_MAX;
}

Vector2 applyCam(Vector2 v, Camera2D cam) {
  return Vector2Add(Vector2Subtract(Vector2Scale(v, cam.zoom), (Vector2){-cam.offset.y, cam.offset.x}), (Vector2){-cam.target.y, cam.target.x});
}

//seed before.
Vector2 getRandomVector2OnScreen(Camera2D cam) {
  Vector2 random = {randSingle() - .5, randSingle() - .5};
  Vector2 randomScaled = {random.x * GetScreenHeight(), random.y * GetScreenWidth()};
  return randomScaled;
}

Vector2 removeCam(Vector2 v, Camera2D cam) {
  return Vector2Subtract(Vector2Add(v, (Vector2){-cam.offset.y, cam.offset.x}), (Vector2){-cam.target.y, cam.target.x});
}
