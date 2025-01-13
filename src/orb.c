#include "orb.h"
#include "circle.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

bool orbInRange(Orb* ob) {
  return Vector2Distance(ob->plr->body.position, ob->body.position) <= orbIntakeRange;
}

Vector2 getPositionFromAngle(float angle, float distance) {
  return (Vector2){cosf(angle) * distance, sinf(angle) * distance};
}

Vector2 getOrbTargetPosition(Orb* ob) {
  float angle = Vector2Angle(ob->plr->body.position, ob->body.position);
  return getPositionFromAngle(angle, ob->distance);
}

void manageOrb(Orb* ob, float delta) {
  if(!ob->valid)
    return;
  if(!ob->approaching) {
    ob->body.position = Vector2Add(ob->body.position, ob->Velocity);
    ob->Velocity = Vector2Scale(ob->Velocity, orbFriction);
    return;
  }
  ob->distance += ob->distanceVel;
  ob->distanceVel += delta * orbSpeed;
  ob->body.position = getOrbTargetPosition(ob);
  if(ob->distance < 0)
    ob->valid = false;
}

void spawnOrbs(Vector2 origin, Orb orbArr[], int spawnCount, Player* plr) {
  for(int i = 0; i < spawnCount; i++) {
    float angle = ((float)rand() / (float)RAND_MAX) * 2 * M_PI;
    float speed = (((float)rand() / (float)RAND_MAX) * (maxOrbSpeed - minOrbSpeed)) + minOrbSpeed;
    Vector2 velocity = {cosf(angle) * speed, sinf(angle) * speed};
    orbArr[i] = (Orb){(circle){origin, orbRadius, orbColour}, velocity, 0, 0, 0, plr, false, true};
  }
}
