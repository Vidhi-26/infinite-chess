#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Board;
class Move;

class Rook:Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    Rook(Colour, Board&);
    virtual ~Rook() = default;
};

#endif
