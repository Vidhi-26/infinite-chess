#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include "PieceFactory.h"
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
            // Simulate that move
            std::pair<Piece*, Piece*> capturedAndOriginalPawn;
            std::unique_ptr<Piece> newPawnPromotionPiece;
            char pawnPromotion = mv.getPawnPromotion();
            if (pawnPromotion == ' ') {
                capturedAndOriginalPawn.first = board.simulateMovePiece(mv);
                capturedAndOriginalPawn.second = nullptr;
            } else {
                // If pawn promotion happens, create a new pawn promotion piece and delete it after simulation
                newPawnPromotionPiece = std::move(PieceFactory::createPiece(pawnPromotion, board));
                capturedAndOriginalPawn = board.simulateMovePiece(mv, newPawnPromotionPiece.get());
            }

            // Check if king will be in check because of move
            if (!board.isKingInCheck(colour)) {
                validMoves.push_back(mv);
            }

            // Undo simulation move
            if (pawnPromotion == ' ') {
                board.undoSimulatedMove(mv, capturedAndOriginalPawn.first);
            } else {
                // If pawn promotion happens, keep track of original pawn for undo
                board.undoSimulatedMove(mv, capturedAndOriginalPawn.first, capturedAndOriginalPawn.second);
            }
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
