#ifndef depositing_h
#define depositing_h

#include "include.h"
#include "circle.h"
#include "player.h"

#define baseIntakeRadius 1200
#define baseRadius 50
#define baseColour GREEN
#define baseIntakeRate 3
#define baseIntakeBorderColour WHITE
#define baseRotationRate .06

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

void drawBase(Base* base, Vector2 screenDimensions);

void manageBase(Base* base, Player* player, Sound* collectionNoise, float delta);

void drawBorder(Base* base, Vector2 screenDimensions);

#endif
