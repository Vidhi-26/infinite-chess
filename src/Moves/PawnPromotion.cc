#include "PawnPromotion.h"

// Ctors (with and without pair)
PawnPromotion::PawnPromotion(int oldRow, int oldCol, int newRow, int newCol, char pawnPromotion) : AbstractMove{oldRow, oldCol, newRow, newCol}, pawnPromotion{pawnPromotion} {}
PawnPromotion::PawnPromotion(std::pair<int, int> oldPos, std::pair<int, int> newPos, char pawnPromotion) : AbstractMove{oldPos, newPos}, pawnPromotion{pawnPromotion} {}

// Getter and setter for pawn promotion
void PawnPromotion::addPawnPromotion(char newPiece) {
    pawnPromotion = newPiece;
}

char PawnPromotion::getPawnPromotion() const {
    return pawnPromotion;
}

// Equals operator
bool PawnPromotion::operator==(const PawnPromotion& other) const {
    return AbstractMove::operator==(other) && pawnPromotion == other.pawnPromotion;
}
