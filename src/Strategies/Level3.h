#ifndef LEVEL3_H
#define LEVEL3_H
#include "Level2.h"
class Move;

class Level3: public Level2 {
protected:
    virtual Move getStrategyImpl(Board&, Colour) override;

public:
    Level3();
    virtual ~Level3() = default;
};

#endif
