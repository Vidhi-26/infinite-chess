#include "Move.h"

// Ctors (with and without pair)
Move::Move(int oldRow, int oldCol, int newRow, int newCol, char pawnPromotion) : oldPos{oldRow, oldCol}, newPos{newRow, newCol}, pawnPromotion{pawnPromotion} {}
Move::Move(std::pair<int, int> oldPos, std::pair<int, int> newPos, char pawnPromotion) : oldPos{oldPos}, newPos{newPos}, pawnPromotion{pawnPromotion} {}

// Getter and setter for pawn promotion
void Move::addPawnPromotion(char newPiece) {
    pawnPromotion = newPiece;
}

char Move::getPawnPromotion() const {
    return pawnPromotion;
}

// Equals operator
bool Move::operator==(const Move& other) const {
    return oldPos == other.oldPos && newPos == other.newPos && pawnPromotion == other.pawnPromotion;
}
