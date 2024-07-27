#ifndef PIECE_H
#define PIECE_H
#include "Colour.h"
#include <vector>

class Board;
class Move;

class Piece {
private:
    virtual std::vector<Move> getPossibleMovesImpl() const = 0;

protected:
    Colour colour;
    Board& board;
    int points;

public:
    Piece(Colour, Board&, int points);
    virtual ~Piece() = default;
    Colour getColour() const;
    
    std::vector<Move> getPossibleMoves();
    int getPoints() const;
};

#endif
