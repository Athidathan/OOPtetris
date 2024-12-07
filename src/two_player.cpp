#include "two_player.h"

TwoPlayer::TwoPlayer() : player1Game(1), player2Game(2) {
    // Initialize the two-player games
}

void TwoPlayer::HandleInput() {
    // Implement separate input handling for each player
    player1Game.HandleInput();
    player2Game.HandleInputPlayer2();
}

void TwoPlayer::Update() {
    player1Game.MoveBlockDown();
    player2Game.MoveBlockDown();
}

void TwoPlayer::Draw() {
    // Draw both games side by side
    player1Game.Draw(0, 0);
    player2Game.Draw(500, 0);
}

bool TwoPlayer::IsGameOver() const {
    return player1Game.gameOver || player2Game.gameOver;
}

Game *TwoPlayer::GetWinner() {
    if (player1Game.score > player2Game.score) 
        return &player1Game;
    else 
        return &player2Game;
}

