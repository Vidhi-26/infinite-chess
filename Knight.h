#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;

public:
    Knight(Colour, Board&);
    virtual ~Knight() = default;
};

#endif
