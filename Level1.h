#ifndef LEVEL1_H
#define LEVEL1_H
#include "Strategy.h"
class Move;

class Level1: public Strategy {
private:
    virtual Move getStrategyImpl(const Board&, Colour) const override;

public:
    Level1();
    virtual ~Level1() = default;
};

#endif