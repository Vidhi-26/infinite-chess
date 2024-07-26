#ifndef MOVE_H
#define MOVE_H
#include <utility>
#include <string>

class Move {
private:
    std::string pawnPromotion = "";
public:
    std::pair<int, int> oldPos;
    std::pair<int, int> newPos;
    void addPawnPromotion(std::string newPiece) {
        pawnPromotion = newPiece;
    }
    Move(int = -1, int = -1, int = -1, int = -1);
};

#endif
