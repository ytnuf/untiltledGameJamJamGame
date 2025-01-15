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
#include "depositing.h"

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

#define missileFiredPath "resources/audio/missileFired.wav"
#define missileBrokePath "resources/audio/missileBroke.wav"
#define playerHitPath "resources/audio/playerHit.wav"
#define playerDeadPath "resources/audio/playerDead.wav"
#define collectionPath "resources/audio/collection.wav"
#define enemyHitPath "resources/audio/enemyHit.wav"

void manageEnemies(enemy** enemyArr, int* enemyCount, Missile** missileArr, int* missileCount, Orb** orbArr, int* orbCount, Player* player, circle* planet, float delta, bool depositing, Sound* missileFiredSound, Sound* enemyHitSound, Vector2 globalScreenDimensions) {
  int i = 0;
  while(*enemyCount != 0 && i < *enemyCount) {
    if(!(*enemyArr)[i].valid) {
      //pop time
      //adding o r b s
      *orbCount += orbSpawnCount;
      *orbArr = realloc(*orbArr, orbSize * *orbCount);
      spawnOrbs((*enemyArr)[i].body.position, &(*orbArr)[*orbCount - orbSpawnCount], orbSpawnCount, &player->body, planet, (*enemyArr)[i].viewDistance);
      PlaySound(*enemyHitSound);
      (*enemyArr)[i] = (*enemyArr)[*enemyCount - 1];
      (*enemyArr) = (enemy*)realloc(*enemyArr, enSize * (*enemyCount)--);
      continue;
    }
    if(depositing) {
      (*enemyArr)[i].seen = true;
      (*enemyArr)[i].speed = enemySpeedAggro;
    } else
      (*enemyArr)[i].speed = enemySpeed;
    Missile tmp;
    tmp.valid = false;
    manageEnemy(&(*enemyArr)[i], &tmp, delta, true, missileFiredSound);
    if(tmp.valid) {
      PlaySound(*missileFiredSound);
      *missileArr = realloc(*missileArr, misSize * ++(*missileCount));
      (*missileArr)[*missileCount - 1] = tmp;
    }
    drawCircle(&(*enemyArr)[i].body, globalScreenDimensions);
    i++;
  }
}

void manageOrbs(Orb** orbArr, int* orbCount, Player* player, float delta, shakeCamera* cam, Base* base, Vector2 globalScreenDimensions, Sound* collectionSound) {
  int i = 0;
  while(*orbCount != 0 && i < *orbCount) {
    if(!(*orbArr)[i].valid) {
      //poopy time
      applyDamage(player, -healthRegenPerOrb);
      if((*orbArr)[i].target != &base->body)
        player->score += scorePerOrb;
      else
        base->score += scorePerOrb;
      PlaySound(*collectionSound);
      (*orbArr)[i] = (*orbArr)[*orbCount - 1];
      (*orbArr) = (Orb*)realloc((*orbArr), orbSize * (*orbCount)--);
      applyCameraShake(cam, 9, 10, (*orbArr)[i].angle);
      continue;
    }
    if(positionInRangeOfBase(base, (*orbArr)[i].body.position)) {
      (*orbArr)[i].target = &base->body;
      (*orbArr)[i].approaching = true;
    }
    manageOrb(&(*orbArr)[i], delta);
    drawCircle(&(*orbArr)[i].body, globalScreenDimensions);
    i++;
  }
}

void manageMissiles(Missile** missileArr, int* missileCount, Player* player, enemy* enemyArr, int* enemyCount, circle* planet, float delta, shakeCamera* cam, Vector2 globalScreenDimensions, Sound* missileBrokeSound, Sound* playerHitSound) {
  int i = 0;
  while(*missileCount != 0 && i < *missileCount) {
    Vector2 vecTo = (*missileArr)[i].velocity;
    if(!(*missileArr)[i].valid) {
      //this is where we pop from stack
      if((*missileArr)[i].body.colour.a >= 250)
        PlaySound(*missileBrokeSound);
      (*missileArr)[i] = (*missileArr)[*missileCount - 1];
      *missileArr = (Missile*)realloc(*missileArr, misSize * (*missileCount)--);
      applyCameraShake(cam, 1, 1, atan2f(vecTo.x, vecTo.y));
      continue;
    }
    if(manageMissileMovement(&(*missileArr)[i], delta, player, cam)) {
      PlaySound(*playerHitSound);
      applyCameraShake(cam, 4, 9, atan2f(vecTo.x, vecTo.y));
    }
    drawCircle(&(*missileArr)[i].body, globalScreenDimensions);
    if(Vector2Distance((*missileArr)[i].body.position, planet->position) <= (*missileArr)[i].body.radius + planet->radius) {
      (*missileArr)[i].valid = false;
      continue;
    }
    for(int b = 0; b < *enemyCount; b++) {
      if(enemyShouldDieToMissile(&enemyArr[b], &(*missileArr)[i])) {
        enemyArr[b].valid = false;
        (*missileArr)[i].valid = false;
        enemyArr[b].viewDistance = atan2f(vecTo.x, vecTo.y);
        applyCameraShake(cam, 2, 5, atan2f(vecTo.x, vecTo.y));
        continue;
      }
    }
    i++;
  }
}

int main() {
  srand(time(NULL));
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  InitAudioDevice();

  Sound playerDeadSound = LoadSound(playerDeadPath);
  Sound playerHitSound = LoadSound(playerHitPath);
  Sound missileBrokeSound = LoadSound(missileBrokePath);
  Sound missileFiredSound = LoadSound(missileFiredPath);
  Sound collectionSound = LoadSound(collectionPath);
  Sound enemyHitSound = LoadSound(enemyHitPath);

  SetTargetFPS(60);
  shakeCamera camera = {(Camera2D){Vector2Scale(screenDimensions, .5), Vector2Scale(screenDimensions, .5),0, .9}, 0, Vector2Zero(), Vector2Zero()};

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero(), playerMaxHealth, playerMaxHealth};

  circle planet = {{4150, 4150}, 5000, planetColour};

  int missileCount = 0;
  Missile* missileArr = (Missile*)malloc(missileCount * misSize);

  Vector2* starArr = initStars(starCount);
  refreshStars(starArr, camera.base, true);

  int enemyCount = 0;
  enemy* enemyArr = (enemy*)malloc(enemyCount * enSize);

  short currentState = gameplayCode;

  float elapsedTime = 0;

  int orbCount = 0;
  Orb* orbArr = (Orb*)malloc(orbCount * orbSize);

  Base base = initBase(planet);

  Vector2 globalScreenDimensions;


  while(!WindowShouldClose()) {
    globalScreenDimensions = (Vector2){GetScreenWidth(), GetScreenHeight()};
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

    drawBorder(&base, globalScreenDimensions);
    drawStars(starArr, &camera.base);
    manageMissiles(&missileArr, &missileCount, &player, enemyArr, &enemyCount, &planet, delta, &camera, globalScreenDimensions, &missileBrokeSound, &playerHitSound);
    manageEnemies(&enemyArr, &enemyCount, &missileArr, &missileCount, &orbArr, &orbCount, &player, &planet, delta, positionInRangeOfBase(&base, player.body.position), &missileFiredSound, &enemyHitSound, globalScreenDimensions);
    manageOrbs(&orbArr, &orbCount, &player, delta, &camera, &base, globalScreenDimensions, &collectionSound);
    manageBase(&base, &player, delta);


    drawCircle(&player.body, globalScreenDimensions);
    drawCircle(&planet, globalScreenDimensions);
    drawBase(&base, globalScreenDimensions);

    DrawText(TextFormat("score: %.0f", base.score), camera.base.target.x - camera.base.offset.x / camera.base.zoom, camera.base.target.y - camera.base.offset.y / camera.base.zoom, 50, WHITE);
    DrawFPS(camera.base.target.x - camera.base.offset.x, camera.base.target.y - camera.base.offset.y);

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
    drawStars(starArr, &camera.base);
    manageMissiles(&missileArr, &missileCount, &player, enemyArr, &enemyCount, &planet, delta, &camera, globalScreenDimensions, &missileBrokeSound, &playerHitSound);
    manageEnemies(&enemyArr, &enemyCount, &missileArr, &missileCount, &orbArr, &orbCount, &player, &planet, delta, positionInRangeOfBase(&base, player.body.position), &missileFiredSound, &enemyHitSound, globalScreenDimensions);
    manageOrbs(&orbArr, &orbCount, &player, delta, &camera, &base, globalScreenDimensions, &collectionSound);
    if(player.health > 0)
      currentState = gameplayCode;
    handleMovment(&player, planet, delta, false);
    drawCircle(&planet, globalScreenDimensions);
    drawCircle(&player.body, globalScreenDimensions);
    DrawText(TextFormat("You are dead your score is %.0f", base.score), camera.base.target.x - camera.base.offset.x, camera.base.target.y - camera.base.offset.y, 100, WHITE);
    DrawText("q to quit r to restart)", camera.base.target.x - camera.base.offset.x, camera.base.target.y - camera.base.offset.y + 100, 50, WHITE);
    if(IsKeyDown(closeKey))
      break;
    if(IsKeyDown(KEY_R))
      system("killall game && ./game");
    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();

  destructStars(starArr);

  return 0;
}
