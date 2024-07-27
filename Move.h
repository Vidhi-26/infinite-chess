#ifndef MOVE_H
#define MOVE_H
#include <utility>
#include <functional>

class Move {
private:
    char pawnPromotion = ' ';
    
public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;

    Move(int = -1, int = -1, int = -1, int = -1);
    Move(std::pair<int, int>, std::pair<int, int>);
    ~Move() = default;

    void addPawnPromotion(char);
    bool operator==(const Move& move) const;
};

#endif
