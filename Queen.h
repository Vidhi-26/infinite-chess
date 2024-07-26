#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Colour, Board&);
    virtual ~Queen() = default;

private:
    std::vector<Move> getPossibleMovesImpl() const override;
};

#endif
