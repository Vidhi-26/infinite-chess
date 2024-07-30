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
MoveMetaData MoveSimulator::simulateMove(Move move, Board& board) {
    std::pair<Piece*, Piece*> capturedAndOriginalPawn;
    std::unique_ptr<Piece> newPawnPromotionPiece;
    char pawnPromotion = move.getPawnPromotion();

        // Simulate move mv
        if (pawnPromotion == ' ') {         // Normal case
            capturedAndOriginalPawn.first = board.simulateMovePiece(move);
            capturedAndOriginalPawn.second = nullptr;
        } else if (pawnPromotion == 'e') {  // En passant case
            capturedAndOriginalPawn.first = nullptr;
            capturedAndOriginalPawn.second = board.simulateMovePiece(move, 'e');
        } else if (pawnPromotion == 'c') {  // Castle case
            capturedAndOriginalPawn.first = nullptr;
            capturedAndOriginalPawn.second = nullptr;
            board.simulateMovePiece(move, 'c');
        } else {                            // Pawn promotion case
            newPawnPromotionPiece = std::move(PieceFactory::createPiece(pawnPromotion, board));
            capturedAndOriginalPawn = board.simulateMovePiece(move, std::move(newPawnPromotionPiece));
        }

        return MoveMetaData{capturedAndOriginalPawn, pawnPromotion};    
}

void MoveSimulator::undoMove(Move move, Board& board, MoveMetaData metaData){
    // Undo simulated move mv
    if (metaData.pawnPromotion == ' ') {         // Normal case
        board.undoSimulatedMove(move, metaData.capturedAndOriginalPawn.first);
    } else if (metaData.pawnPromotion == 'e') {  // En passant case
        board.undoSimulatedMove(move, metaData.capturedAndOriginalPawn.second, 'e');
    } else if (metaData.pawnPromotion == 'c') {  // Castle case
        board.undoSimulatedMove(move);
    } else {                                     // Pawn promotion case
        board.undoSimulatedMove(move, metaData.capturedAndOriginalPawn.first, metaData.capturedAndOriginalPawn.second);
    }
    // /board.render();
}
