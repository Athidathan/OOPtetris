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
