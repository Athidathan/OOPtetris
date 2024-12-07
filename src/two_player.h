// [src/two_player.h](src/two_player.h)
#pragma once
#include "player.h"

class TwoPlayer : public Player {
public:
    TwoPlayer();
    void HandleInput() override;
    void Update() override;
    void Draw() override;
    bool IsGameOver() const override;
    Game* GetWinner() ;
    int getWinnerScore()  { return GetWinner()->score; }
    virtual void Reset() { 
        player1Game.Reset(); 
        player2Game.Reset(); 
    }
private:
    Game player1Game;
    Game player2Game;
};