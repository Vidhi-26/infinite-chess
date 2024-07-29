#ifndef STRATEGY_H
#define STRATEGY_H
#include "unordered_map"
#include "../Colour.h"
class Move;
class Board;

class Strategy {
private:
    virtual Move getStrategyImpl(Board&, Colour) = 0;
public:
    Strategy();
    virtual ~Strategy() = default;
    Move getStrategy(Board&, Colour) ;
};

#endif
