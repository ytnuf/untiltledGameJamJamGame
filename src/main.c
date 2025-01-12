#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include "stdio.h"
#include "circle.h"
#include "missile.h"
#include "player.h"
#include "enemy.h"
#include "stars.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define playerColour WHITE
#define planetColour PURPLE

#define playerDeadColour RED

#define friction .95f

#define cameraLatency .1

#define closeKey KEY_Q

#define misSize sizeof(Missile)

#define gameplayCode 0
#define deadScreenCode 1
#define startScreenCode 2

int main() {
  srand(time(NULL));
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(60);
  Camera2D camera = {Vector2Scale(screenDimensions, .5), Vector2Scale(screenDimensions, .5),0, 1};

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero(), playerMaxHealth, playerMaxHealth};

  circle planet = {{5150, 5150}, 7000, planetColour};

  enemy en = initEnemy((Vector2){-300, -300}, &player, planet);

  Missile tmp = initMissile(Vector2Zero(), Vector2Zero(), 0, 0);
  Missile* missileArr = (Missile*)malloc(0);
  int missileCount = 0;

  circle* starArr = initStars(starCount);

  short currentState = gameplayCode;

  refreshStars(starArr, camera, true);

  while(!WindowShouldClose()) {
    //this is just for health stuff
    player.body.colour = ColorLerp(playerColour, playerDeadColour, 1 - player.health/player.maxHealth);
    if(currentState == deadScreenCode)
      goto deadScreen;
    float delta = GetFrameTime();

    handleMovment(&player, planet, delta);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);

    //camera stuff
    Vector2 plrGlobalPos = {player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};

    refreshStars(starArr, camera, false);

    if(en.valid)
      manageEnemy(&en, &tmp, delta, true);
    tmp.valid = en.valid && tmp.valid;
    if(tmp.valid) {
      missileCount++;
      missileArr = (Missile*)realloc(missileArr, misSize * missileCount);
      missileArr[missileCount - 1] = tmp;
    }

    if(player.health <= 0)
      currentState = deadScreenCode;

    //draw
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(backroundColour);

    unsigned int i = 0;
    while(missileCount != 0 && i < missileCount) {
      if(!missileArr[i].valid) {
        //this is where we pop from stack
        missileArr[i] = missileArr[missileCount - 1];
        missileArr = (Missile*)realloc(missileArr, misSize * (missileCount--));
        continue;
      }
      manageMissileMovement(&missileArr[i], delta, &player);
      drawCircle(&missileArr[i].body);
      if(enemyShouldDieToMissile(&en, &missileArr[i]))
        en.valid = false;
      if(Vector2Distance(missileArr[i].body.position, planet.position) <= missileArr[i].body.radius + planet.radius) {
        missileArr[i].valid = false;
        continue;
      }
      i++;
    }
    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);
    drawCircle(&player.body);
    drawCircle(&planet);
    if(en.valid)
      drawCircle(&en.body);
    printf("%f\n", player.health);

    DrawFPS(Vector2Subtract(camera.target,  camera.offset).x, Vector2Subtract(camera.target, camera.offset).y);

    EndDrawing();

    if(IsKeyDown(closeKey))
      break;
    continue;

  deadScreen:
    //most of this is here so it feels like the world keeps going
    refreshStars(starArr, camera, false);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);
    manageEnemy(&en, &tmp, delta, false);
    plrGlobalPos = (Vector2){player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(backroundColour);
    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);
    drawCircle(&planet);
    drawCircle(&player.body);
    drawCircle(&en.body);
    DrawText("You are dead", camera.target.x - camera.offset.x, camera.target.y - camera.offset.y, 100, WHITE);
    DrawText("q to quit r to restart (the latter isn't implemented)", camera.target.x - camera.offset.x, camera.target.y - camera.offset.y + 100, 50, WHITE);
    if(IsKeyDown(closeKey))
      break;
    EndDrawing();
  }
  CloseWindow();

  destructStars(starArr);

  return 0;
}
