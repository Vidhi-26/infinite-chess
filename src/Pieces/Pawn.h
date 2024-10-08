#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece {
private:
    std::vector<char> pawnPromotions{'q', 'r', 'b', 'n'};
    std::vector<Move> getPossibleMovesImpl() const override;
    char getCodeImpl() const override;
public:
    Pawn(Colour, Board&, int points = 1);
    virtual ~Pawn() = default;
};

#endif
