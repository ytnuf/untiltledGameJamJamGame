#include "player.h"
#include <raylib.h>
#include <raymath.h>

#define prefferedDistFromPlanet 100
#define avoidanceScalar 5

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

void applyInputToVelocity(Player* plr, float delta) {
  Vector2 input = Vector2Scale(getInputVector(up, down, left, right), playerSpeed * delta);
  plr->velocity = Vector2Add(plr->velocity, input);
}

bool applyDamage(Player* plr, float damage) {
  plr->health -= damage;
  return plr->health <= 0;
}

Vector2 getAvoidanceForce(Player* plr, circle planet, float delta) {
  float distFromEdgeWrong = Vector2Distance(plr->body.position, planet.position) - planet.radius;
  float distanceFromEdge = distFromEdgeWrong < 0 ? -distFromEdgeWrong : distFromEdgeWrong;
  if(distanceFromEdge >= prefferedDistFromPlanet)
    return Vector2Zero();
  Vector2 difNormalized = Vector2Normalize(Vector2Subtract(plr->body.position, planet.position));
  return Vector2Scale(difNormalized, (prefferedDistFromPlanet - distanceFromEdge) * delta * avoidanceScalar);
}

void applyAvoidanceForce(Player* plr, circle planet, float delta) {
  plr->velocity = Vector2Add(getAvoidanceForce(plr, planet, delta), plr->velocity);
}

void handleMovment(Player* plr, circle planet, float delta) {
  applyInputToVelocity(plr, delta);
  applyAvoidanceForce(plr, planet, delta);
}
