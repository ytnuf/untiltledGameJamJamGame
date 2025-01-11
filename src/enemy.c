#include "enemy.h"
#include <raylib.h>
#include <raymath.h>

float min(float a, float b) {
  return a < b ? a : b;
}

float max(float a, float b) {
  return a < b ? b : a;
}

enemy initEnemy(Vector2 position, Player* player, circle avoidZone) {
  enemy ret;
  ret.player = player;      //this is a ton less efficient than just doing (enemy){...} (at least on the assembly level)
  ret.avoidZone = avoidZone;//but it's so much more readable thus worth
  ret.maxHealth = enemyMaxHp;
  ret.health = enemyMaxHp;
  ret.body = enemyDefCircle;
  ret.body.position = position;
  ret.speed = enemySpeed;
  ret.damage = enemydefdmng;
  ret.velocity = Vector2Zero();
  ret.viewDistance = enemyViewDistance;
  ret.targetDistance = enemyViewDistance;
  ret.prefDistMaxOffset = 0;
  ret.elapsedShotTime = 0;
  ret.seen = enemyCanSeePlayer(ret);
  return ret;
}

bool tooCloseToPlayer(enemy en) {
  return enemyMinimumDistance > Vector2Distance(en.body.position, en.player->body.position);
}

bool enemyCanSeePlayer(enemy en) {
  return en.viewDistance > Vector2Distance(en.body.position, en.player->body.position);
}

void enemyApplyVelocity(enemy* en) {
  en->body.position = Vector2Add(en->body.position, en->velocity);
}

//this must be called multiple times
void navigateToPoint(enemy* en, Vector2 position, float delta) {
  Vector2 vectorToPoint = Vector2Subtract(position, en->body.position);
  float speed = min(Vector2Length(vectorToPoint), en->speed);
  en->velocity = Vector2Add(Vector2Scale(Vector2Normalize(Vector2Subtract(vectorToPoint, en->velocity)), speed * delta), en->velocity);
}

Vector2 enemyGetTargetPosition(enemy* en) {
  Vector2 difNormal = Vector2Normalize(Vector2Subtract(en->body.position, en->player->body.position));
  return Vector2Add(Vector2Scale(difNormal, en->targetDistance), en->player->body.position);
}

bool enemyTargetInPlanet(enemy* en) {
  return Vector2Distance(en->avoidZone.position, enemyGetTargetPosition(en)) < en->avoidZone.radius;
}

void navigate(enemy* en, float delta) {
  //this is gonna be a complicated function; good thing i have blahaj here to help :)
  //great we're not too close
  //right now lets just have it maintain its previous distance

  en->velocity = Vector2Scale(en->velocity, enemyFric);

  en->targetDistance += ((Vector2Distance(en->body.position, en->player->body.position) - en->targetDistance) * enemyPrefDistanceSmoothing);
  en->targetDistance = (en->targetDistance + enemyPrefDist) / 2.0f;
  if(en->targetDistance < enemyMinimumDistance)
    en->targetDistance = enemyMinimumDistance;

  Vector2 target = enemyGetTargetPosition(en);

  en->seen = en->seen || enemyCanSeePlayer(*en);
  if(en->seen)
    navigateToPoint(en, target, delta);
  if(Vector2Distance(en->body.position, en->avoidZone.position) < en->avoidZone.radius + enemyPreferedAvoidDistance)
    en->velocity = Vector2Add(en->velocity, Vector2Scale(Vector2Normalize(Vector2Subtract(en->body.position, en->avoidZone.position)), (en->avoidZone.radius + enemyPreferedAvoidDistance - Vector2Length(Vector2Subtract(en->body.position, en->avoidZone.position))) * delta)); //here the enemy is too close :/
  enemyApplyVelocity(en);
};
