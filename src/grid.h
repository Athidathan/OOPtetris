#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int column);

    bool IsCellEmpty(int row, int column);
    int ClearFullRows();

private:
    int grid[20][10];
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;

    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    
friend class Game;
};