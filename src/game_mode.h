#pragma once
#include "game.h"

class GameMode {
public:
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool IsGameOver() const = 0;
    virtual ~GameMode() = default;
    virtual Game* GetWinner() = 0;
    virtual int getWinnerScore() = 0;
    virtual void Reset() = 0;
};