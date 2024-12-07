// [src/single_player.h](src/single_player.h)
#pragma once
#include "player.h"

class SinglePlayer : public Player {
public:
    SinglePlayer();
    void HandleInput() override;
    void Update() override;
    void Draw() override;
    bool IsGameOver() const override;
    ~SinglePlayer() override = default;
    Game* GetWinner() ;
    int getWinnerScore()  { return GetWinner()->score; }
    virtual void Reset() { game.Reset(); }
    private:
        Game game;
};