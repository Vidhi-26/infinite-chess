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
    virtual std::vector<Move> getPossibleMovesImpl() const = 0;
    int points;
public:
    Piece(Colour, Board&, int points);
    virtual ~Piece() = default;
    Colour getColour() const;
    
    std::vector<Move> getPossibleMoves() const;
    std::pair<int, int> getPositionOnBoard() const;
    int getPoints() const;
    
};

#endif
