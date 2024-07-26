#ifndef PLAYER_H
#define PLAYER_H
#include "Colour.h"

class Board;
class Move;

class Player {
private:
    Colour colour;
    Board& board;
    virtual Move getMove() const = 0;

public:
    Player(Colour, Board&);
    virtual ~Player() = default;
    
    void playTurn();
    void playTurn(Move);
};

#endif
