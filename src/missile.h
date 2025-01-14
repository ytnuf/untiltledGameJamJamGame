#ifndef missile_h
#define missile_h

#include <raylib.h>
#include <raymath.h>
#include "circle.h"
#include "camera.h"
#include "player.h"

#define missileSpeed 300
#define missileCircl (circle){Vector2Zero(), 5, YELLOW}
#define missileVelocityDampening .991f
#define missileMaxDistance 3000
#define missileMaxLifetime 1.75
#define missileFadeScalar .2
#define missileFadeThreshold 5
#define missileDamageShakeMag 10
#define missileDamageShakeJit 5

struct missile {
  bool valid;
  float damage;
  Vector2 velocity;
  circle* target;
  circle body;
  float lifetime;
};
typedef struct missile Missile;

circle* getClosestTarget(circle* target, circle* arr, int arSize);

Missile initMissile(Vector2 position, Vector2 velocity, float damage, circle* target);

//returns a normalized vector
Vector2 getVectorTo(Vector2 start, Vector2 end);

void manageMissileMovement(Missile* mis, float delta, Player* plr, shakeCamera* cam);

bool missileShouldBreak(Missile* mis);

#endif
