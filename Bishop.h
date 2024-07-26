#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Colour, Board&);
    virtual ~Bishop() = default;

private:
    std::vector<Move> getPossibleMovesImpl() const override;
};

#endif
