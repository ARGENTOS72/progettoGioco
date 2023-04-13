#include <stdio.h>
#include "raylib.h"

int main() {
  InitWindow(320, 320, "Kiriko che boxa il mio pene");

  const int monitor = GetCurrentMonitor();
  const int monitorWidth = GetMonitorWidth(monitor), monitorHeight = GetMonitorHeight(monitor);

  SetWindowSize(monitorWidth, monitorHeight);
  ToggleFullscreen();

  while (!WindowShouldClose()) {
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("SCREEN AREA", monitorWidth / 2 - MeasureText("SCREEN AREA", 32) / 2, 10, 32, RED);

    EndDrawing();
  }

  return 0;
}