#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;
    char getCodeImpl() const override;
public:
    Knight(Colour, Board&, int points = 3);
    virtual ~Knight() = default;
};

#endif
