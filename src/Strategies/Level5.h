#ifndef LEVEL5_H
#define LEVEL5_H
#include "Level4.h"
class Move;

class Level5: public Level4 {
private:
    Move getStrategyImpl(Board&, Colour) override;

public:
    Level5();
    virtual ~Level5() = default;
};

#endif
