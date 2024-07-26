#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    Queen(Colour, Board&);
    virtual ~Queen() = default;
};

#endif
