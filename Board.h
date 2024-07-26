#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <utility>
#include "Piece.h"

class Board {
private:
    std::vector<std::unique_ptr<Piece>> pieces;

public:
    void addPiece(std::unique_ptr<Piece>);
    void removePiece(std::pair<int, int>);

    std::pair<int, int> getPositionOfPiece(const Piece&) const;
    Piece& getPieceAt(int, int) const;
    
    bool isValidPosition(int, int) const;
    bool isEmptyPosition(int, int) const;
    bool isValidConfig();
    void reset();
    void render() const;
    char getState(int, int) const;
    
    bool isGameOver() const;
    Colour getWinner() const;
};

#endif
