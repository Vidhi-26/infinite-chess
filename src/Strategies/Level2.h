#ifndef LEVEL2_H
#define LEVEL2_H
#include "Level1.h"
class Move;

class Level2: public Level1 {
private:
    Move getStrategyImpl(const Board&, Colour) const override;

public:
    Level2();
    virtual ~Level2() = default;
};

#endif
