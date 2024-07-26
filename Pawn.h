#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Board;
class Move;

class Pawn: public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    Pawn(Colour, Board&);
    virtual ~Pawn() = default;
};

#endif
