#include "position.h"

Position::Position(int row, int column)
{
    this->row = row;
    this->column = column;
}

Position Position::operator+(const Position &other) const
{
    return Position(row + other.row, column + other.column);
}
