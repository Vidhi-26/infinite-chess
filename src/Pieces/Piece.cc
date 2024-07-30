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
        std::vector<Move> validMoves;
        for (const auto& mv : allMoves) {
            auto metaData = MoveSimulator::simulateMove(mv, board);
             // Check if king will be in check because of move
            if (!board.isKingInCheck(colour)) {
                validMoves.push_back(mv);
            }
            MoveSimulator::undoMove(mv, board, metaData);
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

bool Piece::hasPieceMoved(std::pair<int, int> pos) const {
    std::stack<Move> history{board.getMoveHistory()};
    while (!history.empty()) {
        Move move = history.top();
        history.pop();
        if (move.oldPos == pos) {
            return true; // Piece has moved
        }
    }
    return false;
}
