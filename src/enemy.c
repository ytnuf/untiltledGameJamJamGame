#include "enemy.h"
#include <raylib.h>
#include <raymath.h>

float min(float a, float b) {
  return a < b ? a : b;
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
  ret.preferedDistance = enemyPrefDist;
  ret.prefDistMaxOffset = 0;
  ret.elapsedShotTime = 0;
  ret.seen = enemyCanSeePlayer(ret);
  return ret;
}

bool tooCloseToPlayer(enemy en) {
  return en.preferedDistance > Vector2Distance(en.body.position, en.player->body.position);
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

void navigate(enemy* en, float delta) {
  //this is gonna be a complicated function; good thing i have blahaj here to help :)
  //great we're not too close
  //right now lets just have it maintain its previous distance

  en->velocity = Vector2Scale(en->velocity, enemyFric);

  Vector2 difNormal = Vector2Normalize(Vector2Subtract(en->player->body.position, en->body.position));

  Vector2 target = Vector2Scale(difNormal, en->previousDistance);

  en->previousDistance += (Vector2Distance(en->body.position, en->player->body.position) - en->previousDistance) * enemyPrefDistanceSmoothing;


  //if(Vector2Distance(en->player->body.position, en->body.position) > en->viewDistance)
  navigateToPoint(en, target, delta);
  enemyApplyVelocity(en);
};
