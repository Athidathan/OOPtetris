#pragma once    
#include "grid.h"
#include "blocks.h"

class Game{
public:
    Game(int playerNumber = 1 );
    ~Game();
    void HandleInput(); 
    void HandleInputPlayer1(); // For player 1 controls
    void HandleInputPlayer2(); // For player 2 controls
    void Draw(int offsetX = 0, int offsetY = 0); // Accept offsets
    void MoveBlockDown();
    void DrawGameOverScreen(Game& winner);
    void Reset();
    bool gameOver;
    int score;
    int playerNumber;
    Font font;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};