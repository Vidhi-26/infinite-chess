#include "Strategy.h"
#include "Move.h"

Strategy::Strategy() {}

Move Strategy::getStrategy(Board& board, Colour colour)  {
    return getStrategyImpl(board, colour);
}
