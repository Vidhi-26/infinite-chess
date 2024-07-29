#include "MoveSimulator.h"
#include "../Pieces/Piece.h"
#include "../Pieces/PieceFactory.h"
#include "../Boards/Board.h"
#include <memory>

// Takes a list of moves (allMoves) and filters based on a condition to return validMoves
// that satisfy the function condition. The condition is if a king is in check or not.
// To verify that king is in check, pass true. Otherwise, false to doesVerifyCheck. Als pass colour of king.
// To check if the condition is satsified, it "simulates" a move on the board, 
// verifies for the condition and then undos it.
std::vector<Move> MoveSimulator::simulateMove(std::vector<Move> allMoves, Board& board, Colour colour, bool doesVerifyCheck) {
    std::vector<Move> validMoves;

    for (const auto& mv : allMoves) {
        // Below fields track pawn promotion
        std::pair<Piece*, Piece*> capturedAndOriginalPawn;
        std::unique_ptr<Piece> newPawnPromotionPiece;
        char pawnPromotion = mv.getPawnPromotion();

        // Simulate move mv
        if (pawnPromotion == ' ') {     // Normal case
            capturedAndOriginalPawn.first = board.simulateMovePiece(mv);
            capturedAndOriginalPawn.second = nullptr;
        } else {                        // Pawn promotion case
            newPawnPromotionPiece = std::move(PieceFactory::createPiece(pawnPromotion, board));
            capturedAndOriginalPawn = board.simulateMovePiece(mv, newPawnPromotionPiece.get());
        }

        // Check if king will be in check because of move
        if (board.isKingInCheck(colour) == doesVerifyCheck) {
            validMoves.push_back(mv);
        }

        // Undo simulated move mv
        if (pawnPromotion == ' ') {     // Normal case
            board.undoSimulatedMove(mv, capturedAndOriginalPawn.first);
        } else {                        // Pawn promotion case
            board.undoSimulatedMove(mv, capturedAndOriginalPawn.first, capturedAndOriginalPawn.second);
        }
    }

    return validMoves;
}
