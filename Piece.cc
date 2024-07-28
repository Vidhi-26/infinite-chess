#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include <iostream>

// Piece ctor
Piece::Piece(Colour colour, Board& board, int points) : colour{colour}, board{board}, points{points} {}

// Get possible moves for a piece
std::vector<Move> Piece::getPossibleMoves(bool isTestingKingInCheck) {
    // Get customized moves depending on Piece type
    std::vector<Move> allMoves = getPossibleMovesImpl();

    if (!isTestingKingInCheck) {
        std::vector<Move> validMoves;
        for (const auto& mv : allMoves) {
            Piece* capturedPiece = board.simulateMovePiece(mv);
            if (!board.isKingInCheck(colour)) {
                validMoves.push_back(mv);
            }
            board.undoSimulatedMove(mv, capturedPiece);
        }
        return validMoves;   
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
