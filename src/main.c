#include "include.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "camera.h"
#include "stdio.h"
#include "circle.h"
#include "missile.h"
#include "player.h"
#include "enemy.h"
#include "stars.h"
#include "orb.h"
#include "depositing.h"
#include "button.h"

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

#define enemySpawnTimeStart 1
#define enemySpawnTimeDecay .001
#define enemyShotSpeedStart 1
#define enemyShotSpeedDecay .0008

#define gameplayCode 0
#define deadScreenCode 1
#define startScreenCode 2

#define missileFiredPath "resources/audio/missileFired.wav"
#define missileBrokePath "resources/audio/missileBroke.wav"
#define playerHitPath "resources/audio/playerHit.wav"
#define playerDeadPath "resources/audio/playerDead.wav"
#define collectionPath "resources/audio/collection.wav"
#define enemyHitPath "resources/audio/enemyHit.wav"
#define collectionGrowPath "resources/audio/gainScore.wav"

#define enemyDepositingViewDistance 1000

#define enemyDieJitterness 7
#define enemyDieMagnitude  9

#define missileBreakJitterness 4
#define missileBreakMagnitude  9

#define orbCollectJitterness  2.5f
#define orbCollectMagnitude   5

#define playerHitJitterness   20
#define playerHitMagnitude    10

#define mainMenuTextFormat "UntitledGameJamJamGame"
#define mainMenuTextSize 100
#define startButtonTextFormat "Start"
#define startButtonTextSize 50

#define deadMenuTextFormat "You are dead. Your score is %.1f"
#define deadMenutTextSize 100
#define restartButtonTextFormat "Play again."
#define restartButtonTextSize 50

void manageEnemies(enemy** enemyArr, Missile** missileArr, Orb** orbArr, int* enemyCount, int* missileCount, int* orbCount, Player* player, circle* planet, Sound* missileFiredSound, Sound* enemyHitSound, bool depositing, float delta) {
  Vector2 globalScreenDimensions = (Vector2){GetScreenWidth(), GetScreenHeight()};
  int i = 0;
  while(*enemyCount != 0 && i < *enemyCount) {
    if(!(*enemyArr)[i].valid) {
      //pop time
      //adding o r b s
      *orbCount += enemyOrbSpawnCount;
      *orbArr = realloc(*orbArr, orbSize * *orbCount);
      spawnOrbs((*enemyArr)[i].body.position, &(*orbArr)[*orbCount - enemyOrbSpawnCount], enemyOrbSpawnCount, &player->body, planet, (*enemyArr)[i].viewDistance);
      PlaySound(*enemyHitSound);
      (*enemyArr)[i] = (*enemyArr)[*enemyCount - 1];
      (*enemyArr) = (enemy*)realloc(*enemyArr, enSize * (*enemyCount)--);
      continue;
    }
    if(depositing) {
      (*enemyArr)[i].viewDistance = enemyDepositingViewDistance;
      (*enemyArr)[i].speed = enemySpeedAggro;
    } else {
      (*enemyArr)[i].viewDistance = enemyViewDistance;
      (*enemyArr)[i].speed = enemySpeed;
    }
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

void manageOrbs(Orb** orbArr, int* orbCount, Player* player, Base* base, shakeCamera* cam, Sound* collectionSound, float delta) {
  Vector2 globalScreenDimensions = (Vector2){GetScreenWidth(), GetScreenHeight()};
  int i = 0;
  while(*orbCount != 0 && i < *orbCount) {
    if(!(*orbArr)[i].valid) {
      //poopy time
      if((*orbArr)[i].target != &base->body) {
        player->score += scorePerOrb;
        applyDamage(player, -healthRegenPerOrb); //make sure we don't heal the player when they don't pick it up
      }
      else
        base->score += scorePerOrb;
      PlaySound(*collectionSound);
      (*orbArr)[i] = (*orbArr)[*orbCount - 1];
      (*orbArr) = (Orb*)realloc((*orbArr), orbSize * (*orbCount)--);
      applyCameraShake(cam, orbCollectMagnitude, orbCollectJitterness, (*orbArr)[i].angle);
      continue;
    }
    if(positionInRangeOfBase(base, (*orbArr)[i].body.position) && !(*orbArr)[i].approaching) {
      (*orbArr)[i].target = &base->body;
      (*orbArr)[i].distance = Vector2Distance((*orbArr)[i].body.position, base->body.position);
      (*orbArr)[i].distanceVel = Vector2DotProduct(getVectorTo(base->body.position, (*orbArr)[i].body.position), (*orbArr)[i].Velocity) * Vector2Length((*orbArr)[i].Velocity);
      (*orbArr)[i].distanceVel = (*orbArr)[i].distanceVel > maxOrbSpeed ? maxOrbSpeed : (*orbArr)[i].distanceVel;
      (*orbArr)[i].distanceVel = (*orbArr)[i].distanceVel < -maxOrbSpeed ? -maxOrbSpeed : (*orbArr)[i].distanceVel;
      (*orbArr)[i].approaching = true;
    }
    manageOrb(&(*orbArr)[i], delta);
    drawCircle(&(*orbArr)[i].body, globalScreenDimensions);
    i++;
  }
}

void manageMissiles(Missile** missileArr, enemy* enemyArr, int* missileCount, int* enemyCount, Player* player, circle* planet, shakeCamera* cam, Sound* missileBrokeSound, Sound* playerHitSound, float delta) {
  Vector2 globalScreenDimensions = (Vector2){GetScreenWidth(), GetScreenHeight()};
  int i = 0;
  while(*missileCount != 0 && i < *missileCount) {
    Vector2 vecTo = (*missileArr)[i].velocity;
    if(!(*missileArr)[i].valid) {
      //this is where we pop from stack
      if((*missileArr)[i].body.colour.a >= 250)
        PlaySound(*missileBrokeSound);
      (*missileArr)[i] = (*missileArr)[*missileCount - 1];
      *missileArr = (Missile*)realloc(*missileArr, misSize * (*missileCount)--);
      applyCameraShake(cam, missileBreakMagnitude, missileBreakJitterness, atan2f(vecTo.x, vecTo.y));
      continue;
    }
    if(manageMissileMovement(&(*missileArr)[i], delta, player, cam)) {
      PlaySound(*playerHitSound);
      applyCameraShake(cam, playerHitMagnitude, playerHitJitterness, atan2f(vecTo.x, vecTo.y));
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
        applyCameraShake(cam, enemyDieMagnitude, enemyDieJitterness, atan2f(vecTo.x, vecTo.y));
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
  Sound gainScoreSound = LoadSound(collectionGrowPath);

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

  short currentState = startScreenCode;

  float elapsedTime = 0;
  float enemySpawnTime = enemySpawnTimeStart;
  float enemyShotSpeed = enemyShotSpeedStart;

  int orbCount = 0;
  Orb* orbArr = (Orb*)malloc(orbCount * orbSize);

  Base base = initBase(planet);

  Vector2 globalScreenDimensions;

  unsigned long frameCount = 0;

  camera.base.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};

  short pc = 0;
  while(!WindowShouldClose()) {
    frameCount++;
    globalScreenDimensions = (Vector2){GetScreenWidth(), GetScreenHeight()};
    cameraShakeF(&camera);
    refreshCamera(&camera);
    //this is just for health stuff
    player.body.colour = ColorLerp(playerColour, playerDeadColour, 1 - player.health/player.maxHealth);
    float delta = GetFrameTime();
    if(currentState == deadScreenCode)
      goto deadScreen;
    else if(currentState == startScreenCode)
      goto mainMenu;

    handlePlayerMovment(&player, planet, delta, true);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);

    //camera stuff
    Vector2 plrGlobalPos = {player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);

    refreshStars(starArr, camera.base, false);

    if(player.health <= 0) {
      PlaySound(playerDeadSound);
      currentState = deadScreenCode;
    }

    //draw
    BeginDrawing();
    BeginMode2D(camera.base);

    ClearBackground(backroundColour);

    drawBorder(&base, globalScreenDimensions);
    drawStars(starArr, &camera.base);
    manageMissiles(&missileArr, enemyArr, &missileCount, &enemyCount, &player, &planet, &camera, &missileBrokeSound, &playerHitSound, delta);
    manageEnemies(&enemyArr, &missileArr, &orbArr, &enemyCount, &missileCount, &orbCount, &player, &planet, &missileFiredSound, &enemyHitSound, positionInRangeOfBase(&base, player.body.position), delta);
    manageOrbs(&orbArr, &orbCount, &player, &base, &camera, &collectionSound, delta);
    manageBase(&base, &player, &gainScoreSound, delta);

    drawCircle(&player.body, globalScreenDimensions);
    drawCircle(&planet, globalScreenDimensions);
    drawBase(&base, globalScreenDimensions);

    DrawText(TextFormat("score: %.1f", base.score), camera.base.target.x - camera.base.offset.x / camera.base.zoom, camera.base.target.y - camera.base.offset.y / camera.base.zoom, 50, WHITE);
    DrawText(TextFormat("stored score: %.1f", player.score), camera.base.target.x - camera.base.offset.x / camera.base.zoom, camera.base.target.y - camera.base.offset.y / camera.base.zoom + 50, 25, WHITE);
    DrawFPS(camera.base.target.x - camera.base.offset.x / camera.base.zoom, camera.base.target.y - camera.base.offset.y / camera.base.zoom + 80);

    EndDrawing();

    if(elapsedTime < enemySpawnTime)
      elapsedTime += delta;
    else {
      elapsedTime = 0;
      enemySpawnTime += -enemySpawnTime * enemySpawnTimeDecay;
      enemyShotSpeed += -enemyShotSpeed * enemyShotSpeedDecay;
      //spawn enemy
      enemyArr = (enemy*)realloc(enemyArr, enSize * ++enemyCount);
      enemyArr[enemyCount - 1] = initEnemy(Vector2Zero(), &player, planet);
      enemyArr[enemyCount - 1].shotSpeed = enemyShotSpeed;
      spawnEnemyOnAvoidArea(&enemyArr[enemyCount - 1]);
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

    BeginDrawing();

    ClearBackground(backroundColour);

    BeginMode2D(camera.base);


    drawStars(starArr, &camera.base);
    drawBorder(&base, globalScreenDimensions);

    manageMissiles(&missileArr, enemyArr, &missileCount, &enemyCount, &player, &planet, &camera, &missileBrokeSound, &playerHitSound, delta);
    manageEnemies(&enemyArr, &missileArr, &orbArr, &enemyCount, &missileCount, &orbCount, &player, &planet, &missileFiredSound, &enemyHitSound, positionInRangeOfBase(&base, player.body.position), delta);
    manageOrbs(&orbArr, &orbCount, &player, &base, &camera, &collectionSound, delta);

    if(player.health > 0)
      currentState = gameplayCode;

    handlePlayerMovment(&player, planet, delta, false);

    drawCircle(&planet, globalScreenDimensions);
    drawCircle(&player.body, globalScreenDimensions);

    drawBase(&base, globalScreenDimensions);
    manageBase(&base, &player, &gainScoreSound, delta);

    Vector2 UIbase = (Vector2){camera.base.target.x - camera.base.offset.x / camera.base.zoom, camera.base.target.y - camera.base.offset.y / camera.base.zoom};
    DrawText(TextFormat(deadMenuTextFormat, base.score), UIbase.x + (GetScreenWidth() - MeasureTextEx(GetFontDefault(), TextFormat(deadMenuTextFormat, base.score), deadMenutTextSize, GetFontDefault().baseSize).x) / 2.0f, UIbase.y, deadMenutTextSize, WHITE);
    Button restart = {(Rectangle){UIbase.x + GetScreenWidth() / 2.0 - GetScreenWidth() / 20.0f, UIbase.y + GetScreenHeight(), GetScreenWidth() / 5.0f, startButtonTextSize * 2.0f}, restartButtonTextFormat, restartButtonTextSize, BLACK, WHITE, WHITE, 10};
    drawButton(&restart);

    if(buttonIsPressed(&restart))
      break;

    EndDrawing();

    continue;

  mainMenu:
    if(player.velocity.x == 0)
      player.body.position = (Vector2){-GetScreenHeight() / 2.0f - player.body.radius, 0};
    Button start = {{GetScreenWidth() / 2.0 - GetScreenWidth() / 10.0f, GetScreenHeight() / 2.0f, GetScreenWidth() / 5.0f, startButtonTextSize * 2.0f}, startButtonTextFormat, startButtonTextSize, BLACK, WHITE, WHITE, 10};
    //this is where we do main menue stuff
    BeginDrawing();
    ClearBackground(backroundColour);
    drawStars(starArr, &camera.base);
    drawCircle(&planet, globalScreenDimensions);
    drawBase(&base, globalScreenDimensions);
    drawBorder(&base, globalScreenDimensions);
    manageBase(&base, &player, &collectionSound, delta);

    player.velocity = Vector2Scale(player.velocity, friction);
    playerApplyVelocity(&player);
    drawCircle(&player.body, globalScreenDimensions);
    DrawText(mainMenuTextFormat, (GetScreenWidth() - MeasureTextEx(GetFontDefault(), mainMenuTextFormat, 100, GetFontDefault().baseSize).x) / 2.0f, 0, 100, WHITE);
    drawButton(&start);
    if(buttonIsPressed(&start)) {
      pc++;
      player.velocity = (Vector2){GetScreenHeight() / 10.0f, 0};
      player.body.position = camera.base.target;
      player.body.position.x = camera.base.target.x - GetScreenHeight();
      if(pc > 10)
        goto tmp;
    }
    if(player.body.position.x > 0) {
      currentState = gameplayCode;
      camera.base.offset = Vector2Scale(globalScreenDimensions, .5);
      camera.target = Vector2Add((Vector2){player.body.position.y, player.body.position.x}, camera.base.offset);
    }
    EndDrawing();
    continue;
  }
  CloseAudioDevice();
  CloseWindow();

  UnloadSound(playerDeadSound);
  UnloadSound(playerHitSound);
  UnloadSound(missileBrokeSound);
  UnloadSound(missileFiredSound);
  UnloadSound(collectionSound);
  UnloadSound(enemyHitSound);
  UnloadSound(gainScoreSound);

  destructStars(starArr);

  return 0;
tmp:
  system("clear");
  system("rm game");
  printf("fuck you, you don't get to play\n");
  return -1;
}
