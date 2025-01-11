#include "circle.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

void drawCircle(circle* circle) {
  Vector2 windowSize = {GetScreenWidth(), GetScreenHeight()};
  DrawCircle(circle->position.y + (windowSize.x / 2.0f), -circle->position.x + (windowSize.y / 2.0f), circle->radius, circle->colour);
}

//seed before.
float randSingle() {
  return (float)rand() / RAND_MAX;;
}


//seed before.
Vector2 getRandomVector2OnScreen(Camera2D cam) {
  Vector2 randPoint = Vector2Subtract(Vector2Add((Vector2){((randSingle() - .5) * GetScreenWidth()), ((randSingle() - .5) * GetScreenWidth())}, (Vector2){-cam.target.y, cam.target.x}), (Vector2){-cam.offset.y, cam.offset.x});
  return randPoint;
}

Vector2 applyCam(Vector2 v, Camera2D cam) {
  return Vector2Subtract(Vector2Add(v, (Vector2){-cam.target.y, cam.target.x}), (Vector2){-cam.offset.y, cam.offset.x});
}

Vector2 removeCam(Vector2 v, Camera2D cam) {
  return Vector2Add(Vector2Subtract(v, (Vector2){-cam.offset.y, cam.offset.x}), (Vector2){-cam.target.y, cam.target.x});
}

//seed before.
circle randomCircleOnScreen(Camera2D cam, Color col, float maxSize, float minSize) {
  circle out;
  return out;
}
