#ifndef orb_h
#define orb_h

#define orbIntakeRange 150
#define orbSpeed 90
#define orbFriction .95
#define maxOrbSpeed 150
#define minOrbSpeed 75

#include "circle.h"
#include "player.h"
#include <raylib.h>
#include <raymath.h>

#define orbColour GREEN
#define orbRadius 5

struct orb {
  circle body;
  Vector2 Velocity;
  float angle;
  float distance;
  float distanceVel;
  Player* plr;
  bool approaching;
  bool valid;
};
typedef struct orb Orb;

bool orbInRange(Orb* ob);

Vector2 getOrbTargetPosition(Orb* ob);

Vector2 getPositionFromAngle(float angle, float distance);

void manageOrb(Orb* ob, float delta);

void spawnOrbs(Vector2 origin, Orb* orbArr, int spawnCount, Player* plr);

#endif
