#ifndef PLAYER_H
#define PLAYER_H
#include "Colour.h"
#include "Move.h"

class Board;

class Player {
private:
    Colour colour;
    Board& board;
    virtual Move getMove() const = 0;

public:
    Player(Colour, Board&);
    virtual ~Player() = default;
    
    void playTurn(const Move& move = Move{-1, -1, -1, -1});
};

#endif
