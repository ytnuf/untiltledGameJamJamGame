#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include "circle.h"
#include "player.h"
#include "enemy.h"
#include "stars.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define playerColour WHITE
#define planetColour PURPLE

#define friction .95f

#define cameraLatency .1

#define closeKey KEY_Q

int main() {
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(60);
  Camera2D camera = {Vector2Scale(screenDimensions, .5), Vector2Scale(screenDimensions, .5),0, 1};

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero()};

  circle planet = {{5150, 5150}, 7000, planetColour};

  enemy en = initEnemy((Vector2){-300, -300}, &player, planet);

  circle* starArr = initStars(starCount);

  while(!WindowShouldClose()) {
    float delta = GetFrameTime();

    applyInputToVelocity(&player, delta);
    playerApplyVelocity(&player);
    player.velocity = Vector2Scale(player.velocity, friction);

    Vector2 plrGlobalPos = {player.body.position.y + GetScreenWidth()/2.0f, -player.body.position.x + GetScreenHeight()/2.0f};

    //camera stuff
    camera.target = Vector2Lerp(camera.target, plrGlobalPos, cameraLatency);
    camera.offset = (Vector2){GetScreenWidth() * .5, GetScreenHeight() * .5};

    refreshStars(starArr, camera);

    //draw
    BeginDrawing();
    BeginMode2D(camera);
    navigate(&en, delta);

    ClearBackground(backroundColour);

    drawCircle(&player.body);
    drawCircle(&planet);
    drawCircle(&en.body);

    for(int i = 0; i < starCount; i++)
      drawCircle(&starArr[i]);

    DrawFPS(Vector2Subtract(camera.target,  camera.offset).x, Vector2Subtract(camera.target, camera.offset).y);

    EndDrawing();

    if(IsKeyDown(closeKey))
      break;
  }
  CloseWindow();

  destructStars(starArr);

  return 0;
}
