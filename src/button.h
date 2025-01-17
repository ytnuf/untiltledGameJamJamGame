#ifndef button_h
#define button_h

#include "include.h"

struct button {
  Rectangle rect;
  char* text;
  int textSize;
  Color rectCol;
  Color textCol;
  Color outlineCol;
  short outlineThickness;
};
typedef struct button Button;

bool buttonIsPressed(Button* button, Camera2D cam);

void drawButton(Button* button);

bool positionInRect(Rectangle rect, Vector2 position);

#endif
