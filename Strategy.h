#ifndef STRATEGY_H
#define STRATEGY_H
#include "unordered_map"
#include "Colour.h"
class Move;
class Board;

class Strategy {
private:
    virtual Move getStrategyImpl(const Board&, Colour) const = 0;
public:
    Strategy();
    virtual ~Strategy() = default;
    Move getStrategy(const Board&, Colour) const;
};

#endif
