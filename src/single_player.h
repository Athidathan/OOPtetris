#pragma once
#include "game_mode.h"

class SinglePlayer : public GameMode {
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