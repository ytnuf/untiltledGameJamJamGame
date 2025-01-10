#include <raylib.h>
#include "circle.h"

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

#define backroundColour BLACK

#define jump KEY_SPACE
#define left KEY_A
#define right KEY_D
#define down KEY_S

#define playerColour WHITE
#define planetColour PURPLE

int main() {
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  SetTargetFPS(24);

  circle player = {{0, 0}, 10, playerColour};
  circle planet = {{1500, 1500}, 2000, planetColour};

  while(!WindowShouldClose()) {

    //draw
    BeginDrawing();

    ClearBackground(backroundColour);

    drawCircle(player);
    drawCircle(planet);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
