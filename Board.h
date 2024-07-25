#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include "Piece.h"

class Board {
private:
    std::vector<std::unique_ptr<Piece>> pieces;

public:
    void reset();
    bool isGameOver() const;
    Colour getWinner() const;
    void render() const;
    char getState(int, int) const;
    void addPiece();
    void removePiece();
};

#endif
