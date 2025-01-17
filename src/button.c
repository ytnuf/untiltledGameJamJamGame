#include "include.h"
#include "button.h"
#include <stdio.h>

bool positionInRect(Rectangle rect, Vector2 position) {
  return position.x - rect.x <= rect.width && position.x - rect.x >= 0 && position.y - rect.y <= rect.height && position.y - rect.y >= 0;
}

bool buttonIsPressed(Button button, Camera2D camera) {
  Vector2 mousePos = Vector2Scale(GetMousePosition(), 1/camera.zoom);
  Vector2 UIbase = (Vector2){camera.target.x - camera.offset.x / camera.zoom, camera.target.y - camera.offset.y / camera.zoom};
  button.rect.x -= UIbase.x;
  button.rect.y -= UIbase.y;
  return positionInRect(button.rect, mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void drawButton(Button* button) {
  DrawRectangleV((Vector2){button->rect.x - button->outlineThickness, button->rect.y - button->outlineThickness}, (Vector2){button->rect.width + button->outlineThickness * 2.0f, button->rect.height + button->outlineThickness * 2.0f}, button->outlineCol);
  DrawRectangleRec(button->rect, button->rectCol);
  Vector2 dems = MeasureTextEx(GetFontDefault(), button->text, button->textSize, GetFontDefault().baseSize);
  DrawText(button->text, (button->rect.width - dems.x) / 2.0f + button->rect.x, button->rect.y + dems.y/2.0f, button->textSize, button->textCol);
}
