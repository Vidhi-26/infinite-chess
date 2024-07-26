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
    void reset();
    bool isGameOver() const;
    Colour getWinner() const;
    void render() const;
    char getState(int, int) const;
    void addPiece(std::unique_ptr<Piece>);
    void removePiece(std::unique_ptr<Piece>);

    std::pair<int, int> getPositionOfPiece(const Piece&) const;
    Piece& getPieceAt(int, int) const;
    
    bool isValidPosition(int, int) const;
    bool isEmptyPosition(int, int) const;    
};

#endif
