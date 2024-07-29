#ifndef MOVE_SIMULATOR_H
#define MOVE_SIMULATOR_H
#include <vector>
#include "Move.h"
#include "../Colour.h"
#include "MoveMetaData.h"

class Board;

class MoveSimulator {
public:
    static MoveMetaData simulateMove(Move, Board&);
    static void undoMove(Move, Board&, MoveMetaData);
    MoveSimulator() = default;
};

#endif  // MOVE_SIMULATOR_H
