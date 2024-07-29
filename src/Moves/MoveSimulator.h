#ifndef MOVE_SIMULATOR_H
#define MOVE_SIMULATOR_H
#include <vector>
#include "Move.h"
#include "../Colour.h"
class Board;

class MoveSimulator {
public:
    static std::vector<Move> simulateMove(std::vector<Move>, Board&, Colour, bool);
};

#endif  // MOVE_SIMULATOR_H
