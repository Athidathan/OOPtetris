#include "game.h"
#include <random>
#include <iostream>

Game::Game(int playerNumber){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    this->playerNumber = playerNumber;
    font = LoadFontEx("Font/Handjet.ttf", 64, 0, 0);
    rotateSound = LoadSound("Sounds/rotate.mp3"); 
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game(){
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    blocks.clear();
}

Block Game::GetRandomBlock(){
    if (blocks.empty())
        blocks = GetAllBlocks();

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}


void Game::Draw(int offsetX, int offsetY) {
    grid.Draw(offsetX, offsetY);

    //print UI
    currentBlock.Draw(offsetX + 11, offsetY + 11);
    DrawTextEx(font, "Score", {(float)(365 + offsetX), (float)(15 + offsetY)}, 38, 2, WHITE);
    char playerText[10];
    sprintf(playerText, "Player %d", playerNumber);
    DrawTextEx(font, playerText, {(float)(365 + offsetX), (float)(500 + offsetY)}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {(float)(370 + offsetX),(float) (175 + offsetY)}, 38, 2, WHITE);
    DrawRectangleRounded({(float) 320 + offsetX,(float) 55 + offsetY, 170, 60}, 0.3, 6, darkGrey);
    char scoreText[10];
    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, { (float) offsetX + 320 + (170 - textSize.x) / 2, (float)offsetY + 65}, 38, 2, WHITE);
    DrawRectangleRounded({(float) 320 + offsetX,(float) 215 + offsetY, 170, 180}, 0.3, 6, darkGrey);
    
    // Preview next block 
    int previewX, previewY;
    switch (nextBlock.id) {
        case 3:
            previewX = offsetX + 255;
            previewY = offsetY + 290;
            break;
        case 4:
            previewX = offsetX + 255;
            previewY = offsetY + 280;
            break;
        default:
            previewX = offsetX + 270;
            previewY = offsetY + 270;
            break;
    }
    nextBlock.Draw(previewX, previewY);
}
// make Handle input  virtual later?
void Game::HandleInput() {
    // Player 1 controls
    if (IsKeyPressed(KEY_A)) MoveBlockLeft();
    if (IsKeyPressed(KEY_D)) MoveBlockRight();
    if (IsKeyPressed(KEY_W)) RotateBlock();
    if (IsKeyPressed(KEY_S))  {
        MoveBlockDown();
        MoveBlockDown();
        UpdateScore(0, 2);}
}

void Game::HandleInputPlayer2() {
    // Player 2 controls
    if (IsKeyPressed(KEY_LEFT)) MoveBlockLeft();
    if (IsKeyPressed(KEY_RIGHT)) MoveBlockRight();
    if (IsKeyPressed(KEY_UP)) RotateBlock();
    if (IsKeyPressed(KEY_DOWN)) {
        MoveBlockDown();
        MoveBlockDown();
        UpdateScore(0, 2);}
}

void Game::MoveBlockLeft(){
    if (!gameOver){
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
            currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight(){
    if (!gameOver){
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
            currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown(){
    if (!gameOver){
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::DrawGameOverScreen(Game &winner)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Game Over!", 100, 150, 40, RED);
    DrawText(TextFormat("Winner: Player %d", winner.playerNumber), 100, 220, 30, WHITE);
    DrawText(TextFormat("Score: %d", winner.score), 100, 260, 30, WHITE);
    DrawText("Press ENTER to restart", 100, 320, 20, LIGHTGRAY);
    EndDrawing();
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // hmmm this line is repeated alot
    for (Position item : tiles){
        if (grid.IsCellOutside(item.row, item.column))
            return true;
    }
    return false;
}

void Game::RotateBlock(){
    if (!gameOver){
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
            currentBlock.UndoRotation();
        else
            PlaySound(rotateSound);
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
        grid.grid[item.row][item.column] = currentBlock.id;

    currentBlock = nextBlock;
    if (BlockFits() == false)
        gameOver = true;

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();

    if (rowsCleared > 0){
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){   
        if (grid.IsCellEmpty(item.row, item.column) == false)
            return false;
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    gameOver = false;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    if (linesCleared == 1) score += 100;
    else if (linesCleared == 2) score += 200;
    else if (linesCleared == 3) score += 400;
    else if (linesCleared == 4) score += 800;
    // No need for else case as we can't break more than 4 lines at once
    score += moveDownPoints;
}
