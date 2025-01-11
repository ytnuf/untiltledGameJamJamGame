#ifndef missile_h
#define missile_h

#include "circle.h"
#include <raylib.h>
#include <raymath.h>

#define missileSpeed 300
#define missileCircl (circle){Vector2Zero(), 5, YELLOW}
#define missileVelocityDampening .99f

struct missile {
  bool valid;
  float damage;
  Vector2 velocity;
  circle* target;
  circle body;
};
typedef struct missile Missile;

circle* getClosestTarget(circle* target, circle* arr, int arSize);

Missile initMissile(Vector2 position, Vector2 velocity, float damage, circle* target);

//returns a normalized vector
Vector2 getVectorTo(Vector2 start, Vector2 end);

void manageMissileMovement(Missile* mis, float delta);

bool missileShouldBreak(Missile* mis);

#endif
