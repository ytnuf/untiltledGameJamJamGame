#include <raylib.h>
#include <raymath.h>
#include "circle.h"
#include "player.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define playerColour WHITE
#define planetColour PURPLE

#define playerR 20
#define playerStartingPosition (Vector2){0, 0}

int main() {
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(24);

  Player player = {(circle){playerStartingPosition, playerR, playerColour}, Vector2Zero()};

  circle planet = {{1500, 1500}, 2000, planetColour};

  while(!WindowShouldClose()) {

    //draw
    BeginDrawing();

    ClearBackground(backroundColour);
    drawCircle(&player.body);
    drawCircle(&planet);

    DrawFPS(0, 0);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
