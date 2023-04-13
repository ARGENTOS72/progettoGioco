#include <stdio.h>
#include "raylib.h" //possibile usare anche le <>

int main() {
  InitWindow(320, 320, "Prova");

  while (!WindowShouldClose()) {
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("SCREEN AREA", 640, 10, 20, RED);

    EndDrawing();
  }

  return 0;
}
