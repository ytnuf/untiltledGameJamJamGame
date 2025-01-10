#ifndef player_h
#define player_h

#include "circle.h"
#include <raylib.h>

#define up KEY_W
#define left KEY_A
#define right KEY_D
#define down KEY_S

struct Player {
  circle body;
  Vector2 velocity;
};
typedef struct Player Player;

void playerApplyVelocity(Player* plr);

Vector2 getInputVector(int l, int r, int u, int d);

#endif
