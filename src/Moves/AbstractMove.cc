#include "AbstractMove.h"

// Ctors (with and without pair)
AbstractMove::AbstractMove(int oldRow, int oldCol, int newRow, int newCol) : oldPos{oldRow, oldCol}, newPos{newRow, newCol} {}
AbstractMove::AbstractMove(std::pair<int, int> oldPos, std::pair<int, int> newPos) : oldPos{oldPos}, newPos{newPos} {}

// Dtor
AbstractMove::~AbstractMove() {}

// Equals operator
bool AbstractMove::operator==(const AbstractMove& other) const {
    return oldPos == other.oldPos && newPos == other.newPos;
}
