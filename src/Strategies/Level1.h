#ifndef LEVEL1_H
#define LEVEL1_H
#include "Strategy.h"
class Move;

class Level1: public Strategy {
protected:
    virtual Move getStrategyImpl(Board&, Colour) override;

public:
    Level1();
    virtual ~Level1() = default;
};

#endif
