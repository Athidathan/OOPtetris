#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    int id;
    // should i have used pair instead of making a class for Position?
    // std::vector<std::pair<int, int>> cells;
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    void Move(const Position& pos);
    void Rotate();
    void UndoRotation();
    std::vector<Position> GetCellPositions();

protected:
    std::map<int, std::vector<Position>> cells;
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
