#include "missile.h"
#include "circle.h"
#include <raymath.h>
#include <raylib.h>
#include <stdlib.h>

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
  return (Missile){true, damage, velocity, target, (circle){position, missileCircl.radius, missileCircl.colour}};
}

Vector2 getVectorTo(Vector2 start, Vector2 end) {
  return Vector2Normalize(Vector2Subtract(end, start));
}

bool missileShouldBreak(Missile* mis) {
  return Vector2Distance(mis->body.position, mis->target->position) < mis->body.radius + mis->target->radius;
}

void manageMissileMovement(Missile* mis, float delta) {
  Vector2 velTerm = Vector2Scale(getVectorTo(mis->body.position, mis->target->position), missileSpeed * delta);
  mis->velocity = Vector2Add(velTerm, mis->velocity);
  //for this we have to step it goes so fast
  Vector2 velTmp = Vector2Scale(mis->velocity, 1.0f/stepCount);
  for(int i = 0; i < stepCount; i++) {
    mis->body.position = Vector2Add(mis->body.position, velTmp);
    mis->valid = !missileShouldBreak(mis);
    if(!mis->valid)
      break;
  }
  mis->velocity = Vector2Scale(mis->velocity, missileVelocityDampening);
}
