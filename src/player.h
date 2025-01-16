#ifndef player_h
#define player_h

#include "circle.h"
#include "include.h"

#define upKey KEY_W
#define leftKey KEY_A
#define rightKey KEY_D
#define downKey KEY_S

#define playerR 20
#define playerStartingPosition (Vector2){0, 0}
#define playerSpeed 100
#define playerMaxHealth 100
#define healthRegenPerOrb 8
#define scorePerOrb 5

struct Player {
  circle body;
  Vector2 velocity;
  float maxHealth;
  float health;
  float score;
};
typedef struct Player Player;

void playerApplyVelocity(Player* plr);

Vector2 getInputVector(int l, int r, int u, int d);

void playerApplyInputToVelocity(Player* plr, float delta);

void applyDamage(Player* plr, float damage);

Vector2 playerGetAvoidanceForce(Player* plr, circle Planet, float delta);

void handlePlayerMovment(Player* plr, circle Planet, float delta, bool readInput);

#endif
