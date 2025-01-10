#include "enemy.h"
#include <raylib.h>
#include <raymath.h>

float min(float a, float b) {
  return a < b ? a : b;
}

enemy initEnemy(Vector2 position, Player player, circle avoidZone) {
  enemy ret;
  ret.player = player;      //this is a ton less efficient than just doing (enemy){...} (at least on the assembly level)
  ret.avoidZone = avoidZone;//but it's so much more readable thus worth
  ret.maxHealth = enemyMaxHp;
  ret.health = enemyMaxHp;
  ret.body = enemyDefCircle;
  ret.speed = enemySpeed;
  ret.damage = enemydefdmng;
  ret.velocity = Vector2Zero();
  ret.viewDistance = enemyViewDistance;
  ret.preferedDistance = enemyPrefDist;
  ret.prefDistMaxOffset = 0;
  ret.elapsedShotTime = 0;
  return ret;
}

bool tooCloseToPlayer(enemy en) {
  return en.preferedDistance > Vector2Distance(en.body.position, en.player.body.position);
}

bool enemyCanSeePlayer(enemy en) {
  return en.viewDistance > Vector2Distance(en.body.position, en.player.body.position);
}

//this must be called recursively
void navigateToPoint(enemy en, Vector2 position, float delta) {
  Vector2 vToPt = Vector2Subtract(position, en.body.position);
  float speed = min(Vector2Length(vToPt), en.speed) * delta;
  en.velocity = Vector2Add(Vector2Scale(Vector2Normalize(vToPt), speed), en.velocity);
}

void navigate(enemy en, float delta) {
  //this is gonna be a complicated function; good thing i have blahaj here to help :)
  if(!enemyCanSeePlayer(en))
    return;
  if(tooCloseToPlayer(en)) //returns true if too close
    goto tooClose;
  //great we're not too close
  //right now lets just have it maintain its previous distance
  navigateToPoint(en, Vector2Scale(Vector2Normalize(Vector2Subtract(en.player.body.position, en.body.position)), en.previousDistance), delta);

  return;
tooClose: //TODO: this label
          //DO STUFF HERE \
  here all we do is get the angle of it and increase the magnitude
}
