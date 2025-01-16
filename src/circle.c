#include "circle.h"
#include <stdlib.h>
#include "../libraries/raylib.h"
#include "../libraries/raymath.h"

#define scalar (Vector2){1, -1}

Vector2 toCartesian(Vector2 v) {
  return (Vector2){-v.y, v.x};
}

void drawCircle(circle* circle, Vector2 screenDimensions) {
  DrawCircle(circle->position.y + (screenDimensions.x / 2.0f), -circle->position.x + (screenDimensions.y / 2.0f), circle->radius, circle->colour);
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
  return (Vector2){(randSingle() - .5) * GetScreenHeight() / cam.zoom, (randSingle() - .5) * GetScreenWidth() / cam.zoom};
}

Vector2 removeCam(Vector2 v, Camera2D cam) {
  return Vector2Add(v, (Vector2){-cam.offset.y + cam.target.y, cam.offset.x - cam.target.x});
}
