#ifndef healthbar_h
#define healthbar_h

#include <raylib.h>

struct healthbar {
  Vector2 position;
  float width;
  float height;
  float borderWidth;
  float percentage;
  Color borderColour;
  Color fillColour;
};
typedef struct healthbar Healthbar;

void drawHealthbar(Healthbar bar);

#endif
