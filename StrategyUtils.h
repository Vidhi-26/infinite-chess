#ifndef STRATEGY_UTILS_H
#define STRATEGY_UTILS_H
#include "Move.h"
#include <vector>

class StrategyUtils {
public:
    static Move getRandomMove(std::vector<Move>);
};

#endif
