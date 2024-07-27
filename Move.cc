#include "Move.h"

Move::Move(int oldRow, int oldCol, int newRow, int newCol) : oldPos{oldRow, oldCol}, newPos{newRow, newCol} {}

void Move::addPawnPromotion(std::string newPiece) {
    pawnPromotion = newPiece;
}

bool Move::operator==(const Move& other) {
    return oldPos == other.oldPos && newPos == other.newPos;
}
