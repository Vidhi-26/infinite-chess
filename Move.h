#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Move {
private:
    char pawnPromotion = ' ';
    
public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;

    Move(int = -1, int = -1, int = -1, int = -1);
    Move(std::pair<int, int>, std::pair<int, int>);
    
    ~Move() = default;
    Move(const Move&) = default;
    Move(Move&&) = default;
    Move& operator=(const Move&) = default;
    Move& operator=(Move&&) = default;

    void addPawnPromotion(char);
    bool operator==(const Move& move);
};

#endif
