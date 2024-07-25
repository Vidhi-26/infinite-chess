#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Move {
public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;

    Move(int, int, int, int);
};

#endif
