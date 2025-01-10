#include "circle.h"
#include <raylib.h>

void drawCircle(circle* circle) {
  Vector2 windowSize = {GetScreenWidth(), GetScreenHeight()};
  DrawCircle(circle->position.x + (windowSize.x / 2.0f), -circle->position.y + (windowSize.y / 2.0f), circle->radius, circle->colour);
}
