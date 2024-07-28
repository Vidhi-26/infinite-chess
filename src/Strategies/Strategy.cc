#include "Strategy.h"
#include "../Moves/Move.h"

Strategy::Strategy() {}

Move Strategy::getStrategy(const Board& board, Colour colour) const {
    return getStrategyImpl(board, colour);
}
