#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
private:
    std::vector<Move> getPossibleMovesImpl() const override;
    
public:
    Bishop(Colour, Board&);
    virtual ~Bishop() = default;
};

#endif
