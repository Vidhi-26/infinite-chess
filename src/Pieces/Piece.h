#ifndef PIECE_H
#define PIECE_H
#include "../Colour.h"
#include <vector>

class Board;
class Move;

class Piece {
private:
    virtual std::vector<Move> getPossibleMovesImpl() const = 0;
    virtual char getCodeImpl() const = 0;
protected:
    Colour colour;
    Board& board;
    int points;

public:
    Piece(Colour, Board&, int points);
    virtual ~Piece() = default;
    Colour getColour() const;
    char getCode() const;
    std::vector<Move> getPossibleMoves(bool isTestingKingInCheck = false);
    int getPoints() const;
    bool hasPieceMoved(std::pair<int, int>) const;
};

#endif
