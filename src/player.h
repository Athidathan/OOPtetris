// [src/player.h](src/player.h)
#pragma once
#include "game.h"

class Player {
public:
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool IsGameOver() const = 0;
    virtual ~Player() = default;
    virtual Game* GetWinner() = 0;
    virtual int getWinnerScore() = 0;
    virtual void Reset() = 0;
};