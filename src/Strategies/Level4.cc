#include "Level3.h"
#include "Level4.h"
#include "../Boards/Board.h"
#include "../Pieces/Piece.h"
#include "../Colour.h"
#include "../Moves/Move.h"
#include <unordered_map>
#include <climits>
#include "ColourUtils.h"

Level4::Level4() {}

std::vector<Move> getAllLegalMoves(Board& board, Colour colour) {
    std::vector<Move> legalMoves;
    for(auto it = board.begin(); it != board.end(); ++it){
        if((*it).isEmpty()) continue;
        auto piece = (*it).piece;
        if (piece->getColour() == colour) {
            std::vector<Move> pieceMoves = piece->getPossibleMoves();
            legalMoves.insert(legalMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return legalMoves;
}


int evaluateBoard(const Board& board, Colour colour) {
    int score = 0;
    for(auto it = board.cend(); it != board.cend(); ++it) {
        if((*it).isEmpty()) continue;
        auto piece = (*it).piece;
        if (piece->getColour() == colour) {
            score += piece->getPoints();
        } else {
            score -= piece->getPoints();
        }
    }
    return score;
}

int minimax(Board& board, int depth, bool isMaximizingPlayer, Colour colour, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board, colour);
    }

    std::vector<Move> legalMoves = getAllLegalMoves(board, colour);

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (const auto& move : legalMoves) {
            Piece* capturedPiece = board.simulateMovePiece(move);
            int eval = minimax(board, depth - 1, false, ColourUtils::oppositeColour(colour), alpha, beta);
            board.undoSimulatedMove(move, capturedPiece);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (const auto& move : legalMoves) {
            Piece* capturedPiece = board.simulateMovePiece(move);
            int eval = minimax(board, depth - 1, true, ColourUtils::oppositeColour(colour), alpha, beta);
            board.undoSimulatedMove(move, capturedPiece);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}



Move Level4::getStrategyImpl(Board& board, Colour colour) {
    int bestValue = INT_MIN;
    Move bestMove;
    std::vector<Move> legalMoves = getAllLegalMoves(board, colour);  // Assume Board has getAllLegalMoves method

    for (const auto& move : legalMoves) {
        Piece* capturedPiece = board.simulateMovePiece(move);
        int moveValue = minimax(board, 3, false, ColourUtils::oppositeColour(colour), INT_MIN, INT_MAX); // Depth 3 for example
        board.undoSimulatedMove(move, capturedPiece);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    return bestMove;
}



