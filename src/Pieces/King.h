#ifndef KING_H
#define KING_H
#include "Piece.h"
#include "limits.h"

class King : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;
    char getCodeImpl() const override;
public:
    King(Colour, Board&, int points = 1000);
    virtual ~King() = default;
};

#endif
