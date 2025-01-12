#include "missile.h"
#include "circle.h"
#include "player.h"
#include <raymath.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define stepCount 15

circle* getClosestTarget(circle* target, circle* arr, int arSize) {
  int closestTIndex = -1;
  float closestDist = RAND_MAX;
  while(--arSize >= 0) {
    float dist = Vector2Distance(target->position, arr[arSize].position);
    if(dist > closestDist)
      continue;
    
    closestDist = dist;
    closestTIndex = arSize;
  }
  return &arr[closestTIndex];
}

Missile initMissile(Vector2 position, Vector2 velocity, float damage, circle* target) {
  return (Missile){true, damage, velocity, target, (circle){position, missileCircl.radius, missileCircl.colour}, 0};
}

Vector2 getVectorTo(Vector2 start, Vector2 end) {
  return Vector2Normalize(Vector2Subtract(end, start));
}

bool missileShouldBreak(Missile* mis) {
  return Vector2Distance(mis->body.position, mis->target->position) < mis->body.radius + mis->target->radius || Vector2Distance(mis->body.position, mis->target->position) > missileMaxDistance;
}

void manageMissileMovement(Missile* mis, float delta, Player* plr) {
  Vector2 velTerm = Vector2Scale(getVectorTo(mis->body.position, mis->target->position), missileSpeed * delta);
  mis->velocity = Vector2Add(velTerm, mis->velocity);
  //for this we have to step it goes so fast
  Vector2 velTmp = Vector2Scale(mis->velocity, 1.0f/stepCount);
  for(int i = 0; i < stepCount; i++) {
    mis->body.position = Vector2Add(mis->body.position, velTmp);
    mis->valid = !missileShouldBreak(mis);
    if(!mis->valid) {
      applyDamage(plr, mis->damage);
      break;
    }
  }
  mis->velocity = Vector2Scale(mis->velocity, missileVelocityDampening);
  mis->lifetime += delta;
  mis->valid = mis->lifetime < missileMaxLifetime && mis->valid;
}
