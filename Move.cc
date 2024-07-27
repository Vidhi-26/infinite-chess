#include "Move.h"

Move::Move(int oldRow, int oldCol, int newRow, int newCol) : oldPos{oldRow, oldCol}, newPos{newRow, newCol} {}
Move::Move(std::pair<int, int> oldPos, std::pair<int, int> newPos) : oldPos{oldPos}, newPos{newPos} {}

void Move::addPawnPromotion(char newPiece) {
    pawnPromotion = newPiece;
}

bool Move::operator==(const Move& other) const {
    return oldPos == other.oldPos && newPos == other.newPos && pawnPromotion == other.pawnPromotion;
}
