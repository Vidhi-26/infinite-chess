#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
public:
    King(Colour, Board&);
    virtual ~King() = default;

private:
    std::vector<Move> getPossibleMovesImpl() const override;
};

#endif
