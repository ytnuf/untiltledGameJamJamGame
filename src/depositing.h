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
#define rotationRate .06

struct base {
  float score;
  circle body;
  float intakeRadius;
  float angle;
  circle planet;
};
typedef struct base Base;

void setBasePosition(Base* base);

void addScoreToBase(Base* base, float score);

Base initBase(circle planet);

bool positionInRangeOfBase(Base* base, Vector2 position);

void drawBase(Base* base);

void manageBase(Base* base, Player* player, float delta);

void drawBorder(Base* base);

#endif
