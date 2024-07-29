#ifndef LEVEL4_H
#define LEVEL4_H
#include "Level4.h"
#include "Level3.h"
class Move;

class Level4: public Level3 {
private:
    Move getStrategyImpl(Board&, Colour) override;

public:
    Level4();
    virtual ~Level4() = default;
};

#endif
