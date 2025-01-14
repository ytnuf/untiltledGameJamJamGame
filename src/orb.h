#ifndef orb_h
#define orb_h

#define orbIntakeRange 150
#define orbStartingDist 200
#define orbSpeed -90
#define orbFriction .95
#define maxOrbSpeed 50
#define minOrbSpeed 25
#define orbAvoidRadius 100

#include "circle.h"
#include "player.h"
#include <raylib.h>
#include <raymath.h>

#define orbColour GREEN
#define orbRadius 5
#define orbLifeToGrab .25
#define defaultOrbChunkSize 100

struct orb {
  circle body;
  Vector2 Velocity;
  float angle;
  float distance;
  float distanceVel;
  circle* target;
  bool approaching;
  bool valid;
  float lifetime;
  circle* avoidArea;
};
typedef struct orb Orb;

bool orbInRange(Orb* ob);

Vector2 getOrbTargetPosition(Orb* ob);

Vector2 getPositionFromAngle(float angle, float distance);

void manageOrb(Orb* ob, float delta);

void spawnOrbs(Vector2 origin, Orb* orbArr, int spawnCount, circle* target, circle* avoidArea, float bias);

#endif
