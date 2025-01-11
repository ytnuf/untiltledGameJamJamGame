#ifndef player_h
#define player_h

#include "circle.h"
#include <raylib.h>

#define up KEY_W
#define left KEY_A
#define right KEY_D
#define down KEY_S

#define playerR 20
#define playerStartingPosition (Vector2){0, 0}
#define playerSpeed 100

struct Player {
  circle body;
  Vector2 velocity;
  float maxHealth;
  float health;
};
typedef struct Player Player;

void playerApplyVelocity(Player* plr);

Vector2 getInputVector(int l, int r, int u, int d);

void applyInputToVelocity(Player* plr, float delta);

bool applyDamage(Player* plr, float damage);

#endif
