#ifndef enemy_h
#define enemy_h

#include "circle.h"
#include "player.h"
#include <raylib.h>
#include <raymath.h>

#define enemyMaxHp 15
#define enemydefdmng 3
#define enemyPrefDist 200
#define enemySpeed 100
#define enemyDefShotSpeed .5f
#define enemyDefCircle (circle){(Vector2){0, 0}, 10, RED};
#define enemyViewDistance 300
#define enemyPrefDistanceSmoothing .1
#define enemyMinimumDistance

#define enemyFric .8

struct enemy {
  Vector2 velocity;
  circle body;
  circle avoidZone;
  float health;
  float maxHealth;
  float damage;
  float speed;
  Player* player;
  float preferedDistance;
  float prefDistMaxOffset;
  float elapsedShotTime;
  float shotSpeed;
  float viewDistance;
  float previousDistance;
  bool seen;
};
typedef struct enemy enemy;

enemy initEnemy(Vector2 position, Player* player, circle planet);

bool tooCloseToPlayer(enemy en);

bool enemyCanSeePlayer(enemy en);

void navigate(enemy* en, float delta);

#endif
