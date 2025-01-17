#include "powerup.h"
#include "missile.h"
#include "circle.h"
#include "enemy.h"
#include "include.h"
#include <stdlib.h> //for big number

bool shouldDropPowerup(unsigned int enCount) {
  return randSingle() <= powerUpChance && enCount > 0;
}

void applyPowerup(Missile* misArr, unsigned int misCount, circle* target) {
  while(--misCount > 0)
    misArr[misCount].target = target;
}

int shouldApplyPowerup(Camera2D camera, enemy* enArr, unsigned int enCount) {
  if(enCount == 0)
    return false;
  Vector2 mousePos = Vector2Scale(GetMousePosition(), 1/camera.zoom);
  float distanceSqr = (powerUpSelectionGive + enArr[0].body.radius) * (powerUpSelectionGive + enArr[0].body.radius);
  unsigned int closestEnemyI = 0; //can't be null or negative /shrug
  float closestEnemyDist = RAND_MAX; //(big number)
  for(unsigned int i = 0; i < enCount; i++) {
    float dist = Vector2DistanceSqr(enArr[i].body.position, mousePos);
    if(dist > closestEnemyDist) //avoid nesting !1!1111 (makes it faster too!)
      continue;
    closestEnemyDist = dist;
    closestEnemyI = i;
  }
  return closestEnemyDist > distanceSqr ? -1 : closestEnemyI;
}
