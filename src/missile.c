#include "missile.h"
#include "circle.h"
#include "player.h"
#include "camera.h"
#include "include.h"

#define stepCount 15

const float maxDistSqr = missileMaxDistance * missileMaxDistance;

Missile initMissile(Vector2 position, Vector2 velocity, float damage, circle* target) {
  return (Missile){true, damage, velocity, target, (circle){position, missileCircl.radius, missileCircl.colour}, 0};
}

Vector2 getVectorTo(Vector2 start, Vector2 end) {
  return Vector2Normalize(Vector2Subtract(end, start));
}

bool missileShouldBreak(Missile* mis) {
  Vector2 bodyPos = mis->body.position;
  Vector2 tarBodPos = mis->target->position;
  float distSqr = Vector2DistanceSqr(bodyPos, tarBodPos);
  return  distSqr < mis->target->radius * mis->target->radius || distSqr > maxDistSqr;
}

bool manageMissileMovement(Missile* mis, float delta, Player* plr, shakeCamera* cam) {
  bool ret = false;
  Vector2 velTerm = Vector2Scale(getVectorTo(mis->body.position, mis->target->position), missileSpeed * delta);
  mis->velocity = Vector2Add(velTerm, mis->velocity);
  //for this we have to step it goes so fast
  Vector2 velTmp = Vector2Scale(mis->velocity, 1.0f/stepCount);
  for(int i = 0; i < stepCount; i++) {
    mis->body.position = Vector2Add(mis->body.position, velTmp);
    mis->valid = !missileShouldBreak(mis);
    if(!mis->valid) {
      applyDamage(plr, mis->damage);
      applyCameraShake(cam, missileDamageShakeMag, missileDamageShakeJit, atan2f(mis->velocity.x, mis->velocity.y));
      ret = true;
      break;
    }
  }
  mis->velocity = Vector2Scale(mis->velocity, missileVelocityDampening);
  mis->lifetime += delta;
  mis->body.colour.a += mis->lifetime > missileMaxLifetime ? -mis->body.colour.a * missileFadeScalar : 0;
  mis->valid = mis->valid && mis->body.colour.a >= missileFadeThreshold;
  return ret;
}
