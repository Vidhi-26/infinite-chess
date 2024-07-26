#ifndef PLAYER_H
#define PLAYER_H
#include "Colour.h"
#include "Move.h"

class Board;

class Player {
private:
    virtual Move getMove(const Move& move) const = 0;

protected:
    Colour colour;
    Board& board;    

public:
    Player(Colour, Board&);
    virtual ~Player() = default;
    
    void playTurn(const Move& move = Move());
};

#endif
