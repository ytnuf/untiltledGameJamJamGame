#include "button.h"
#include "include.h"

bool positionInRect(Rectangle rect, Vector2 position) {
  return rect.x < position.x && rect.x + rect.width > position.x && rect.y < position.y && rect.y + rect.height > position.y;
}

bool buttonIsPressed(Button* button) {
  Vector2 mousePos = GetMousePosition();
  return positionInRect(button->rect, mousePos) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

void drawButton(Button* button) {
  DrawRectangleRec(button->rect, button->rectCol);
  DrawText(button->text, button->rect.x, button->rect.y + button->rect.height / 2.0f - button->textSize / 2.0f, button->textSize, button->textCol);
}
