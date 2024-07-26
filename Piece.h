#ifndef PIECE_H
#define PIECE_H
#include "Colour.h"
#include <vector>

class Board;
class Move;

class Piece {
private:
    Colour colour;
    Board& board;
    virtual std::vector<Move> getPossibleMovesImpl() const = 0;

public:
    Piece(Colour, Board&);
    virtual ~Piece() = default;
    
    std::vector<Move> getPossibleMoves() const;
    std::pair<int, int> getPositionOnBoard() const;
};

#endif
