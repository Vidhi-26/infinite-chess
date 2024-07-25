#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Board;
class Move;

class Knight:Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    Knight(Colour, Board&);
    virtual ~Knight() = default;
};

#endif
