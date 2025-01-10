#include "player.h"
#include <raylib.h>
#include <raymath.h>

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
