#include <raylib.h>
#include <raymath.h>
#include <game.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    InitWindow(1920, 1080, "Point and Stick");

    SetTargetFPS(60);
    SetRandomSeed(time(0));
    Setup();
    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}