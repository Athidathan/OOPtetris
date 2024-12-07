#include "game.h"
#include <random>

Game::Game(int playerNumber){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    this->playerNumber = playerNumber;
    font = LoadFontEx("Font/Handjet.ttf", 64, 0, 0);
}

Game::~Game(){
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
    currentBlock.Draw(offsetX + 11, offsetY + 11);
    DrawTextEx(font, "Score", {(float)(365 + offsetX), (float)(15 + offsetY)}, 38, 2, WHITE);
    char playerText[10];
    sprintf(playerText, "Player %d", playerNumber);
    DrawTextEx(font, playerText, {(float)(365 + offsetX), (float)(500 + offsetY)}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {(float)(370 + offsetX),(float) (175 + offsetY)}, 38, 2, WHITE);
    // Preview next block with adjusted positions
    DrawRectangleRounded({(float) 320 + offsetX,(float) 55 + offsetY, 170, 60}, 0.3, 6, darkGrey);
    char scoreText[10];
    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, { (float) offsetX + 320 + (170 - textSize.x) / 2, (float)offsetY + 65}, 38, 2, WHITE);
    DrawRectangleRounded({(float) 320 + offsetX,(float) 215 + offsetY, 170, 180}, 0.3, 6, darkGrey);
    
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
// make this virtual later?
void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
    switch (keyPressed){
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        // Soft drop
        MoveBlockDown();
        MoveBlockDown();
        UpdateScore(0, 2);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

// [src/game.cpp](src/game.cpp)
void Game::HandleInputPlayer1() {
    // Player 1 controls
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
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
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
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
    DrawText("Game Over!", 200, 150, 40, RED);
    DrawText(TextFormat("Winner: Player %d", winner.playerNumber), 200, 220, 30, WHITE);
    DrawText(TextFormat("Score: %d", winner.score), 200, 260, 30, WHITE);
    DrawText("Press ENTER to restart", 200, 320, 20, LIGHTGRAY);
    EndDrawing();
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // should i have used a reference here? this line is repeated alot
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

    if (rowsCleared > 0)
        UpdateScore(rowsCleared, 0);
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
    switch (linesCleared){
    case 1:
        score += 100;
        break;
    case 2:
        score += 200;
        break;
    case 3:
        score += 400;
        break;
    case 4:
        score += 800;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}
