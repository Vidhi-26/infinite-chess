#ifndef PLAYER_H
#define PLAYER_H
#include "../Colour.h"
#include "../Moves/Move.h"

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
    
    Move playTurn(const Move& move = Move());
};

#endif
