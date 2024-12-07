#include "single_player.h"

SinglePlayer::SinglePlayer() : game(1) {
    // Initialize the single-player game
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


