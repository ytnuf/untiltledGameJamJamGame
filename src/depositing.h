#ifndef depositing_h
#define depositing_h

#include <raylib.h>
#include "circle.h"
#include "player.h"

#define baseIntakeRadius 650
#define baseRadius 50
#define baseColour GREEN
#define intakeRate 1
#define intakeBorderColour WHITE
#define intakeBorderThickn 20

struct base {
  float score;
  circle body;
  float intakeRadius;
};
typedef struct base Base;

void addScoreToBase(Base* base, float score);

Base initBase(circle planet);

bool positionInRangeOfBase(Base* base, Vector2 position);

void drawBase(Base* base);

void manageBase(Base* base, Player* player, float delta);

void drawBorder(Base* base);

#endif
