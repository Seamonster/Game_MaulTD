#include "maultd/core/game_state.h"
#include "maultd/core/hex_grid.h"

#include <raylib.h>

#include <string>

namespace
{

constexpr int kScreenWidth = 1280;
constexpr int kScreenHeight = 720;
constexpr double kFixedTimestepSeconds = 1.0 / 60.0;

void drawGrid(const maultd::core::tHexGrid& grid)
{
    constexpr Vector2 origin{120.0F, 96.0F};

    for (int row = 0; row < grid.rows(); ++row)
    {
        for (int col = 0; col < grid.cols(); ++col)
        {
            const auto center = grid.hexCenter({row, col});
            const Vector2 screenCenter{origin.x + center.X, origin.y + center.Y};
            const auto color = grid.isOccupied({row, col}) ? RED : DARKGRAY;

            DrawPolyLines(screenCenter, 6, grid.hexRadius(), 30.0F, color);
        }
    }
}

} // namespace

int main()
{
    InitWindow(kScreenWidth, kScreenHeight, "Game Maul TD");
    SetTargetFPS(60);

    maultd::core::tGameState game{maultd::core::tHexGrid{9, 13, 32.0F}};
    double accumulator = 0.0;

    while (!WindowShouldClose())
    {
        accumulator += GetFrameTime();

        while (accumulator >= kFixedTimestepSeconds)
        {
            game.update(kFixedTimestepSeconds);
            accumulator -= kFixedTimestepSeconds;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game Maul TD", 32, 24, 28, BLACK);
        DrawText("Milestone 1: Raylib window, fixed timestep, and hex grid scaffold", 32, 60, 18, DARKGRAY);

        drawGrid(game.grid());

        const auto elapsed = "Logic time: " + std::to_string(game.elapsedSeconds()).substr(0, 5) + "s";
        DrawText(elapsed.c_str(), 32, kScreenHeight - 48, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
