#include "Colour.h"
#ifndef STRATEGY_H
#define STRATEGY_H

class Move;
class Board;

class Strategy {
private:
    virtual Move getStrategyImpl(const Board&, Colour) const = 0;

public:
    Strategy();
    virtual ~Strategy() = default;
    Move getStrategy() const;
};

#endif