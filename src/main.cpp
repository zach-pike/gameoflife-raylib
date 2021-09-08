#include "raylib.h"
#include "math.h"
#include "grid/grid.h"
#include "stdio.h"

int main(void) {

    bool autoMove = false;
    bool loadOrSave = false;

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(0, 0, "");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    ToggleFullscreen();

    //--------------------------------------------------------------------------------------

    Grid grid(GetScreenWidth(), GetScreenHeight());

    float lastUpdated = 0.0f;
    float textTimer = 0.0f;

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(BLACK);

            //draw the grid and update it
            grid.DrawGrid();
            grid.UpdateGrid();

            int pressed = GetKeyPressed();

            if (pressed >= (int)'1' && pressed <= (int)'9') {
                if (loadOrSave) {
                    grid.ExportGrid(pressed - 48);
                } else {
                    grid.LoadGrid(pressed - 48);
                }
            }


            //auto move key
            if (IsKeyReleased(KEY_A)) autoMove = !autoMove;
            if (IsKeyReleased(KEY_R)) grid.ResetGrid();

            if (IsKeyReleased(KEY_LEFT_CONTROL)) loadOrSave = !loadOrSave;

            //if automove is on and it is time to move then run gol code
            if (GetTime() - lastUpdated > 0.06f && autoMove) {
                grid.GameOfLife();
                lastUpdated = GetTime();
            }

            DrawFPS(GetScreenWidth() / 2, 0);

            //draw info text
            DrawText(FormatText("AutoMove is %s, %s mode", autoMove ? "on" : "off", loadOrSave ? "save" : "load"), 0, 0, 28, DARKBLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}