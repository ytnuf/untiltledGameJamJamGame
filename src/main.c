#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "camera.h"
#include "stdio.h"
#include "circle.h"
#include "missile.h"
#include "player.h"
#include "enemy.h"
#include "stars.h"
#include "orb.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define playerColour WHITE
#define planetColour PURPLE

#define playerDeadColour RED

#define friction .96f

#define cameraLatency .08

#define closeKey KEY_Q

#define misSize sizeof(Missile)
#define enSize sizeof(enemy)
#define orbSize sizeof(Orb)

#define enemySpawnTime 1

#define gameplayCode 0
#define deadScreenCode 1
#define startScreenCode 2

void manageEnemies(enemy** enemyArr, int* enemyCount, Missile** missileArr, int* missileCount, Orb** orbArr, int* orbCount, Player* player, circle* planet, float delta) {
  int i = 0;
  while(*enemyCount != 0 && i < *enemyCount) {
    printf("%d enemyCount\n", *enemyCount);
    if(!(*enemyArr)[i].valid) {
      //pop time
      //adding o r b s
      printf("enemy %d not valid\n", i);
      *orbCount += orbSpawnCount;
      *orbArr = realloc(*orbArr, orbSize * *orbCount);
      spawnOrbs((*enemyArr)[i].body.position, &(*orbArr)[*orbCount - orbSpawnCount], orbSpawnCount, player, planet);
      (*enemyArr)[i] = (*enemyArr)[*enemyCount - 1];
      (*enemyArr) = (enemy*)realloc(*enemyArr, enSize * *enemyCount--);
      continue;
    }
    Missile tmp;
    tmp.valid = false;
    manageEnemy(&(*enemyArr)[i], &tmp, delta, true);
    if(tmp.valid) {
      *missileArr = realloc(*missileArr, misSize * ++(*missileCount));
      (*missileArr)[*missileCount - 1] = tmp;
    }
    drawCircle(&(*enemyArr)[i].body);
    i++;
  }
}

void manageOrbs(Orb** orbArr, int* orbCount, Player* player, float delta) {
  int i = 0;
  while(*orbCount != 0 && i < *orbCount) {
    printf("orb loop %d with orb count %d\n", i, *orbCount);
    if(!(*orbArr)[i].valid) {
      //poopy time
      printf("healing and deallocationg\n");
      applyDamage(player, -healthRegenPerOrb);
      (*orbArr)[i] = (*orbArr)[*orbCount - 1];
      (*orbArr) = (Orb*)realloc((*orbArr), orbSize * (*orbCount)--);
      continue;
    }
    printf("managing orb %d\n", i);
    manageOrb(&(*orbArr)[i], delta);
    printf("drawing orb %d\n", i);
    drawCircle(&(*orbArr)[i].body);
    i++;
  }
}

void manageMissiles(Missile** missileArr, int* missileCount, Player* player, enemy** enemyArr, int* enemyCount, circle* planet, float delta) {
  int i = 0;
  while(*missileCount != 0 && i < *missileCount) {
    printf("missile loop %d\n", i);
    printf("checking if valid\n");
    if(!(*missileArr)[i].valid) {
      //this is where we pop from stack
      (*missileArr)[i] = (*missileArr)[*missileCount - 1];
      *missileArr = (Missile*)realloc(*missileArr, misSize * (*missileCount)--);
      continue;
    }
    printf("managing missile %d\n", i);
    manageMissileMovement(&(*missileArr)[i], delta, player);
    printf("drawing missile %d\n", i);
    drawCircle(&(*missileArr)[i].body);
    if(Vector2Distance((*missileArr)[i].body.position, planet->position) <= (*missileArr)[i].body.radius + planet->radius) {
      (*missileArr)[i].valid = false;
      continue;
    }
    for(int b = 0; b < *enemyCount; b++) {
      if(enemyShouldDieToMissile(&(*enemyArr)[b], &(*missileArr)[i]))
        (*enemyArr)[b].valid = false;
    }
    i++;
  }
}

int main() {
  srand(time(NULL));
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(60);
  shakeCamera camera = {(Camera2D){Vector2Scale(screenDimensions, .5), Vector2Scale(screenDimensions, .5),0, .9}, 0, Vector2Zero(), Vector2Zero()};

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero(), playerMaxHealth, playerMaxHealth};

  circle planet = {{4150, 4150}, 5000, planetColour};

  int missileCount = 0;
  Missile* missileArr = (Missile*)malloc(missileCount * misSize);

  circle* starArr = initStars(starCount);
  refreshStars(starArr, camera.base, true);

  int enemyCount = 0;
  enemy* enemyArr = (enemy*)calloc(enemyCount, enSize);

  short currentState = gameplayCode;

  float elapsedTime = 0;

  int orbCount = 0;
  Orb* orbArr = (Orb*)malloc(orbCount * orbSize);

  applyCameraShake(&camera, 10, 10, 0);
  while(!WindowShouldClose()) {
    cameraShakeF(&camera);
    refreshCamera(&camera);
    //this is just for health stuff
    player.body.colour = ColorLerp(playerColour, playerDeadColour, 1 - player.health/player.maxHealth);
    float delta = GetFrameTime();
    if(currentState == deadScreenCode)
      goto deadScreen;

    handleMovment(&player, planet, delta, true);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);

    //camera stuff
    Vector2 plrGlobalPos = {player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.base.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};

    refreshStars(starArr, camera.base, false);

    if(player.health <= 0)
      currentState = deadScreenCode;

    //draw
    BeginDrawing();
    BeginMode2D(camera.base);

    ClearBackground(backroundColour);

    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);
    printf("%d\n", enemyCount);
    manageMissiles(&missileArr, &missileCount, &player, &enemyArr, &enemyCount, &planet, delta);
    manageEnemies(&enemyArr, &enemyCount, &missileArr, &missileCount, &orbArr, &orbCount, &player, &planet, delta);
    manageOrbs(&orbArr, &orbCount, &player, delta);

    drawCircle(&player.body);
    drawCircle(&planet);

    DrawFPS(Vector2Subtract(camera.target,  camera.base.offset).x, Vector2Subtract(camera.target, camera.base.offset).y);

    EndDrawing();

    if(elapsedTime < enemySpawnTime)
      elapsedTime += delta;
    else {
      elapsedTime = 0;
      //spawn enemy
      enemyArr = (enemy*)realloc(enemyArr, enSize * ++enemyCount);
      enemyArr[enemyCount - 1] = initEnemy(Vector2Zero(), &player, planet);
      spawnEnemyAvoidArea(&enemyArr[enemyCount - 1]);
    }

    if(IsKeyDown(closeKey))
      break;
  continue;

deadScreen:
    //most of this is here so it feels like the world keeps going
    refreshStars(starArr, camera.base, false);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);
    plrGlobalPos = (Vector2){player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.base.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};
    BeginDrawing();
    BeginMode2D(camera.base);
    ClearBackground(backroundColour);
    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);
    if(player.health > 0)
      currentState = gameplayCode;
    handleMovment(&player, planet, delta, false);
    drawCircle(&planet);
    drawCircle(&player.body);
    DrawText("You are dead", camera.base.target.x - camera.base.offset.x, camera.base.target.y - camera.base.offset.y, 100, WHITE);
    DrawText("q to quit r to restart)", camera.base.target.x - camera.base.offset.x, camera.base.target.y - camera.base.offset.y + 100, 50, WHITE);
    if(IsKeyDown(closeKey))
      break;
    if(IsKeyDown(KEY_R))
      system("killall game && ./game");
    EndDrawing();
  }
  CloseWindow();

  destructStars(starArr);

  return 0;
}
