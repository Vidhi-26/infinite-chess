#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    King(Colour, Board&);
    virtual ~King() = default;
};

#endif
