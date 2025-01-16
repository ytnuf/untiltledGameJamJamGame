#ifndef button_h
#define button_h

#include "include.h"

struct button {
  Rectangle rect;
  char* text;
  int textSize;
  Color rectCol;
  Color textCol;
};
typedef struct button Button;

bool buttonIsPressed(Button* button);

void drawButton(Button* button);

bool positionInRect(Rectangle rect, Vector2 position);

#endif
