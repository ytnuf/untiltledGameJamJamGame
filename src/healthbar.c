#include "healthbar.h"
#include <raylib.h>
#include <raymath.h>

void drawHealthbar(Healthbar bar) {
  Rectangle fill = {bar.position.x - bar.width / 2.0f, bar.position.y + bar.height / 2.0f,
                    bar.width * bar.percentage, bar.height};
  Rectangle border = {bar.position.x - bar.borderWidth, bar.position.y + bar.borderWidth, bar.width + (2.0f * bar.borderWidth), bar.height + (2.0f * bar.borderWidth)};
  DrawRectangleRec(fill, bar.fillColour);
  DrawRectangleRec(border, bar.borderColour);
}
