#ifndef ABSTRACT_MOVE_H
#define ABSTRACT_MOVE_H
#include <utility>
#include <functional>

class AbstractMove {
protected:
    // == operator
    bool operator==(const AbstractMove& move) const;

public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;

    // Ctors and virutal dtor
    AbstractMove(int = -1, int = -1, int = -1, int = -1);
    AbstractMove(std::pair<int, int>, std::pair<int, int>);
    virtual ~AbstractMove() = 0;
};

#endif  // ABSTRACT_MOVE_H
