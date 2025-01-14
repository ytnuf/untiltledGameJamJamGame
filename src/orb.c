#include "orb.h"
#include "missile.h"
#include "circle.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

bool orbInRange(Orb* ob) {
  return Vector2Distance(ob->target->position, ob->body.position) <= orbIntakeRange;
}

Vector2 getPositionFromAngle(float angle, float distance) {
  return (Vector2){cosf(angle) * distance, sinf(angle) * distance};
}

Vector2 getOrbTargetPosition(Orb* ob) {
  Vector2 dif = getVectorTo(ob->target->position, ob->body.position);
  float angle = atan2f(dif.y, dif.x);
  return Vector2Add(getPositionFromAngle(angle, ob->distance), ob->target->position);
}

Vector2 getOrbAvoidForce(Orb* ob, float delta) {
  Vector2 dif = getVectorTo(ob->avoidArea->position, ob->body.position);
  float distanceFromEdge = ob->avoidArea->radius - Vector2Distance(ob->avoidArea->position, ob->body.position);
  if(distanceFromEdge + orbAvoidRadius < 0)
    return Vector2Zero();
  float scalar = (ob->avoidArea->radius + orbAvoidRadius - Vector2Distance(ob->avoidArea->position, ob->body.position)) * delta;
  return Vector2Scale(dif, scalar);
}

void manageOrb(Orb* ob, float delta) {
  if(!ob->valid)
    return;
  ob->lifetime += delta;
  if(!ob->approaching) {
    ob->body.position = Vector2Add(ob->body.position, ob->Velocity);
    ob->Velocity = Vector2Scale(ob->Velocity, orbFriction);
    ob->Velocity = Vector2Add(ob->Velocity, getOrbAvoidForce(ob, delta));
    ob->approaching = orbInRange(ob) && ob->lifetime >= orbLifeToGrab;
    if(ob->approaching) {
      ob->distanceVel = 200 * delta;
      ob->distance = ceilf(Vector2Distance(ob->body.position, ob->target->position) / defaultOrbChunkSize) * defaultOrbChunkSize;
    }
    return;
  }
  ob->distance += ob->distanceVel;
  ob->distanceVel += delta * orbSpeed;
  ob->body.position = getOrbTargetPosition(ob);
  if(ob->distance < 0)
    ob->valid = false;
}

void spawnOrbs(Vector2 origin, Orb orbArr[], int spawnCount, circle* target, circle* avoidArea, float bias) {
  for(int i = 0; i < spawnCount; i++) {
    float randVal = randSingle();
    float angle = (((randVal * randVal * randVal * randVal) - .5f) * 2.0f * M_PI) + bias;
    float speed = (((float)rand() / (float)RAND_MAX) * (maxOrbSpeed - minOrbSpeed)) + minOrbSpeed;
    Vector2 velocity = {cosf(angle) * speed, sinf(angle) * speed};
    orbArr[i] = (Orb){(circle){origin, orbRadius, orbColour}, velocity, 0, 0, 0, target, false, true, 0, avoidArea};
  }
}
