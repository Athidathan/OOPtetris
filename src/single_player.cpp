// [src/single_player.cpp](src/single_player.cpp)
#include "single_player.h"

SinglePlayer::SinglePlayer() {
    // Initialize the single-player game
    game = Game(1);
}

void SinglePlayer::HandleInput() {
    game.HandleInput();
}

void SinglePlayer::Update() {
    game.MoveBlockDown();
}

void SinglePlayer::Draw() {
    game.Draw();
}

bool SinglePlayer::IsGameOver() const {
    return game.gameOver;
}
Game *SinglePlayer::GetWinner(){
    return &game;
}


