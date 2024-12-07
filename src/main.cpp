#include <raylib.h>
#include "game.h"
#include <iostream>
#include "single_player.h"
#include "two_player.h"
#include <stdexcept>  // For exception handling
double lastUpdateTime = 0;
bool EventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
int ShowTitleScreen() {
    int mode = 0;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("TETRIS", 125, 100, 50, WHITE);
        DrawText("Press 1 for Single Player", 100, 200, 20, WHITE);
        DrawText("Press 2 for Two Players", 100, 250, 20, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            mode = 1;
            break;
        } else if (IsKeyPressed(KEY_TWO)) {
            mode = 2;
            break;
        }
    }
    return mode;
}


int main() {
    try {
        InitWindow(500, 620, "Tetris");
        SetTargetFPS(60);
        InitAudioDevice();
        Music music = LoadMusicStream("Sounds/music.mp3");
        PlayMusicStream(music);
        int mode = ShowTitleScreen();

        Player* game = nullptr;
        if (mode == 1) {
            game = new SinglePlayer();
        } else if (mode == 2) {
            SetWindowSize(1000, 620); // Adjust window size for two-player mode
            game = new TwoPlayer();
        } else {
            throw std::runtime_error("Invalid game mode selected.");
        }

        while (!WindowShouldClose()) {
            
            if (game->IsGameOver()) {
                // Determine the winner
                Game* winner = game->GetWinner();
                winner->DrawGameOverScreen(*winner);
                // Restart mechanism
                if (IsKeyPressed(KEY_ENTER)) {
                    game->Reset();
                    SeekMusicStream(music, 0);
            }
            } else {
                UpdateMusicStream(music);
                game->HandleInput();
                if (EventTriggered(0.2)) {
                    game->Update();
                }

                BeginDrawing();
                ClearBackground(BLACK);
                game->Draw();
                EndDrawing();
            } 
        }
        UnloadMusicStream(music);
        game->Reset();
        CloseAudioDevice();
        CloseWindow();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;  
}