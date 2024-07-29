#include "Piece.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"
#include "PieceFactory.h"
#include "../Moves/MoveSimulator.h"
#include <iostream>

// Piece ctor
Piece::Piece(Colour colour, Board& board, int points) : colour{colour}, board{board}, points{points} {}

// Get possible moves for a piece
std::vector<Move> Piece::getPossibleMoves(bool isTestingKingInCheck) {
    // Get customized moves depending on Piece type
    std::vector<Move> allMoves = getPossibleMovesImpl();
     
    if (!isTestingKingInCheck) {
        return MoveSimulator::simulateMove(allMoves, board, this->colour, false);
    }

    return allMoves;
}

// Getters for colour and points
Colour Piece::getColour() const {
    return colour;
}

int Piece::getPoints() const {
    return points;
}

char Piece::getCode() const{
    return getCodeImpl();
}
