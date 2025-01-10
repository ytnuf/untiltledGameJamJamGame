#include <raylib.h>

#define screenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}

int main() {
  InitWindow(screenDimensions.x, screenDimensions.y, "cool game :)");
  while(!WindowShouldClose()) {
    
  }
  CloseWindow();
  return 0;
}
