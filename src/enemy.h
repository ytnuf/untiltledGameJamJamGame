#ifndef enemy_h
#define enemy_h

#include "../libraries/raylib.h"
#include "../libraries/raymath.h"
#include "circle.h"
#include "player.h"
#include "missile.h"

#define enemyMaxHp 15
#define enemydefdmng 3
#define enemyPrefDist 300
#define enemySpeed 100
#define enemySpeedAggro 200
#define enemyDefShotSpeed 1.0f
#define enemyDefCircle (circle){(Vector2){0, 0}, 10, RED}
#define enemyViewDistance 900
#define enemyPrefDistanceSmoothing .1
#define enemyMinimumDistance 300
#define enemyPreferedAvoidDistance 550
#define enemyAvoidZonePrefDistance 100
#define enemyKnockBack 50
#define enemyFiringRange 650
#define enemyHitboxRadius 70
#define enemyMissileDetectionMinimumLifetime .1 //this is a long name basically it just is the minimum time a missile has to exist for it to hit an enemy
#define enemyOrbSpawnCount 3

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
  float prefDistMaxOffset;
  float elapsedShotTime;
  float shotSpeed;
  float viewDistance;
  float targetDistance;
  bool seen;
  bool valid;
};
typedef struct enemy enemy;

enemy initEnemy(Vector2 position, Player* player, circle planet);

bool enemyRooCloseToPlayer(enemy en);

bool enemyCanSeePlayer(enemy en);

void enemyNavigate(enemy* en, float delta);

bool enemyTargetIsInPlanet(enemy* en);

bool enemyShouldSpawnMissile(enemy* en);

void manageEnemy(enemy* en, Missile* out, float delta, bool canShoot, Sound* missileFiredSound);

bool enemyShouldDieToMissile(enemy* en, Missile* mis);

void spawnEnemyOnAvoidArea(enemy* in);

#endif
