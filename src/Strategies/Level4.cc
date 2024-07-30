#include "Level4.h"
#include "../Boards/Board.h"
#include "../Pieces/Piece.h"
#include "../Colour.h"
#include "../Moves/Move.h"
#include "StrategyUtils.h"
#include <set>
#include "../Moves/MoveSimulator.h"

Level4::Level4() {}

Move Level4::getStrategyImpl(Board& board, Colour colour) {
    Move bestMove{};
    int bestScore = -1;
    std::vector<Move> checkMoves;
    std::vector<Move> safeMoves;
    std::vector<Move> centerControlMoves;

    // Central squares
    std::set<std::pair<int, int>> centerSquares = {
        {3, 3}, {3, 4}, {4, 3}, {4, 4}
    };

    for (auto it = board.cbegin(); it != board.cend(); ++it) {
        const Square& square = *it;
        if (square.isEmpty()) continue;
        
        auto piece = square.piece;
        if (piece->getColour() != colour) continue;
        std::vector<Move> moves = piece->getPossibleMoves();
        
        for (auto& move : moves) {
            if (board.isEmptyPosition(move.newPos.first, move.newPos.second)) {
                board.movePiece(move);
                if (board.isKingInCheck(colour == Colour::BLACK ? Colour::WHITE : Colour::BLACK)) {
                    checkMoves.push_back(move);
                }
                if (centerSquares.count({move.newPos.first, move.newPos.second}) > 0) {
                    centerControlMoves.push_back(move);
                }
                board.movePiece(Move(move.newPos, move.oldPos));
            } else {
                Piece& enemy = board.getPieceAt(move.newPos.first, move.newPos.second);
                if (enemy.getColour() != colour && enemy.getPoints() > bestScore) {
                    bestMove = move;
                    bestScore = enemy.getPoints();
                }
            }

            // Simulate the move to check for king safety and potential double attacks
            auto metadata = MoveSimulator::simulateMove(move, board);
            bool isKingSafe = !board.isKingInCheck(colour);
            bool isMoveSafe = true;

            for (auto it2 = board.begin(); it2 != board.end(); ++it2) {
                auto enemySquare = (*it2);
                if (enemySquare.isEmpty() || enemySquare.piece->getColour() == colour) continue;
                auto enemyMoves = enemySquare.piece->getPossibleMoves();
                for (auto& emove : enemyMoves) {
                    if (emove.newPos.first == move.newPos.first && emove.newPos.second == move.newPos.second) {
                        isMoveSafe = false;
                        break;
                    }
                }
                if (!isMoveSafe) break;
            }
            MoveSimulator::undoMove(move, board, metadata);

            if (isKingSafe && isMoveSafe) {
                safeMoves.push_back(move);
            }
        }
    }

    // Prioritize check moves
    if (!checkMoves.empty()) {
        return StrategyUtils::getRandomMove(checkMoves);
    }

    // If no check moves, prioritize safe moves
    if (!safeMoves.empty()) {
        return StrategyUtils::getRandomMove(safeMoves);
    }

    // If no safe moves, prioritize center control moves
    if (!centerControlMoves.empty()) {
        return StrategyUtils::getRandomMove(centerControlMoves);
    }

    // If no other move found, use the best capture move
    if (bestMove.newPos.first != -1 && bestMove.newPos.second != -1) {
        return bestMove;
    }

    // If no good move found, use Level 3 strategy
    return Level3::getStrategyImpl(board, colour);
}
