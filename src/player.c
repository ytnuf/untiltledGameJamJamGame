#include "player.h"
#include "../libraries/raylib.h"
#include "../libraries/raymath.h"

#define prefferedDistFromPlanet 100
#define avoidanceScalar 6

void playerApplyVelocity(Player* plr) {
  plr->body.position = Vector2Add(plr->body.position, plr->velocity);
}

Vector2 getInputVector(int l, int r, int u, int d) {
  Vector2 out = Vector2Zero();
  out.x += IsKeyDown(l);
  out.x -= IsKeyDown(r);
  out.y -= IsKeyDown(u);
  out.y += IsKeyDown(d);
  return Vector2Normalize(out);
}

void playerApplyInputToVelocity(Player* plr, float delta) {
  Vector2 input = Vector2Scale(getInputVector(upKey, downKey, leftKey, rightKey), playerSpeed * delta);
  plr->velocity = Vector2Add(plr->velocity, input);
}

void applyDamage(Player* plr, float damage) {
  plr->health -= damage;
  if(plr->health > plr->maxHealth)
    plr->health = plr->maxHealth;
  if(plr->health < 0)
    plr->health = 0;
}

Vector2 playerGetAvoidanceForce(Player* plr, circle planet, float delta) {
  float distFromEdgeWrong = Vector2Distance(plr->body.position, planet.position) - planet.radius;
  float distanceFromEdge = distFromEdgeWrong < 0 ? -distFromEdgeWrong : distFromEdgeWrong;
  if(distanceFromEdge >= prefferedDistFromPlanet)
    return Vector2Zero();
  Vector2 difNormalized = Vector2Normalize(Vector2Subtract(plr->body.position, planet.position));
  return Vector2Scale(difNormalized, distanceFromEdge * delta * avoidanceScalar);
}

void playerApplyAvoidanceForce(Player* plr, circle planet, float delta) {
  plr->velocity = Vector2Add(playerGetAvoidanceForce(plr, planet, delta), plr->velocity);
}

void handlePlayerMovment(Player* plr, circle planet, float delta, bool readInput) {
  if(readInput)
    playerApplyInputToVelocity(plr, delta);
  playerApplyAvoidanceForce(plr, planet, delta);
}
