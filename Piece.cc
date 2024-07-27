#include "Piece.h"
#include "Board.h"

// Piece ctor
Piece::Piece(Colour colour, Board& board, int points) : colour{colour}, board{board}, points{points} {}

// Get possible moves for a piece
std::vector<Move> Piece::getPossibleMoves(bool isTestingKingInCheck = false) {
    // Get customized moves depending on Piece type
    std::vector<Move> allMoves = getPossibleMovesImpl();

    if (!isTestingKingInCheck) {
        std::vector<Move> validMoves;
        for (const auto& mv : allMoves) {
            board.movePiece(mv);
            if (!board.isKingInCheck(colour)) {
                validMoves.push_back(mv);
            }
            board.simpleUndoMove(mv);
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
