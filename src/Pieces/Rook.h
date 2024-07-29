#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;
    char getCodeImpl() const override;
public:
    Rook(Colour, Board&, int points = 5);
    virtual ~Rook() = default;
};

#endif
