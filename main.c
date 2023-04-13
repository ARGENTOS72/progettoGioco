#include <stdio.h>
#include "raylib.h"

typedef struct {
  float xPos;
  float yPos;
  int width;
  int height;
} Player;

int main() {
  InitWindow(320, 320, "Kiriko che boxa il mio pene");

  const int monitor = GetCurrentMonitor();
  const int monitorWidth = GetMonitorWidth(monitor), monitorHeight = GetMonitorHeight(monitor);

  SetWindowSize(monitorWidth, monitorHeight);
  ToggleFullscreen();

  Player player = {
    10.0, 10.0, 10, 10,
  };

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_A)) {
      player.xPos -= 0.5;
    }

    if (IsKeyDown(KEY_D)) {
      player.xPos += 0.5;
    }

    if (IsKeyDown(KEY_W)) {
      player.yPos -= 0.5;
    }

    if (IsKeyDown(KEY_S)) {
      player.yPos += 0.5;
    }

    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle((int) player.xPos, (int) player.yPos, player.width, player.height, RED);

    EndDrawing();
  }

  return 0;
}
