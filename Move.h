#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Move {
public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;

    Move(int = -1, int = -1, int = -1, int = -1);
};

#endif
