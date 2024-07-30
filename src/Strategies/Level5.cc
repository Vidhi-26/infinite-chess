#include "Level3.h"
#include "Level5.h"
#include "../Boards/Board.h"
#include "../Pieces/Piece.h"
#include "../Colour.h"
#include "../Moves/Move.h"
#include <unordered_map>
#include <climits>
#include "../ColourUtils.h"
#include "../Moves/MoveSimulator.h"
#include <iostream>

Level5::Level5() {}

/*
Referred to the following sources:
https://blog.devgenius.io/simple-min-max-chess-ai-in-python-2910a3602641
https://github.com/apostolisv/chess-ai
https://medium.com/tech-tavern/how-to-build-a-chess-ai-with-python-89c824a2b330
*/

//Helper method to return all the legal moves of a colour
std::vector<Move> getAllLegalMoves(Board& board, Colour colour) {
    std::vector<Move> legalMoves;
    for(auto it = board.cbegin(); it != board.cend(); ++it){
        if((*it).isEmpty()) continue;
        auto piece = (*it).piece;
        if (piece->getColour() == colour) {
            std::vector<Move> pieceMoves = piece->getPossibleMoves();
            legalMoves.insert(legalMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return legalMoves;
}

//Evaluates the board: More pieces => better position for the colour
int evaluateBoard(const Board& board, Colour colour) {
    int score = 0;

    //Iterate through the board and add up the values of all the pieces of the specified colour
    for(auto it = board.cbegin(); it != board.cend(); ++it) {
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

//Standard minimax recursive algorithm with alpha beta pruning
int minimax(Board& board, int depth, bool isMaximizingPlayer, Colour colour, int alpha, int beta) {
    
    //Base Case
    if (depth == 0) {
        return evaluateBoard(board, colour);
    }
    std::vector<Move> legalMoves = getAllLegalMoves(board, colour);

    //Maximizing player's turn
    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (const auto& move : legalMoves) {

            //Simulate a move
            auto metadata = MoveSimulator::simulateMove(move, board);

            //Recursive function call
            int eval = minimax(board, depth - 1, false, ColourUtils::oppositeColour(colour), alpha, beta);

            //Undo the move
            MoveSimulator::undoMove(move, board, metadata);
            maxEval = std::max(maxEval, eval);

            //Alpha beta pruning
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } 
    
    //Minimizing player's turn
    else {
        int minEval = INT_MAX;
        for (const auto& move : legalMoves) {

            //Simulate a move
            auto metadata = MoveSimulator::simulateMove(move, board);

            //Recursive call
            int eval = minimax(board, depth - 1, true, ColourUtils::oppositeColour(colour), alpha, beta);

            //Undo the move
            MoveSimulator::undoMove(move, board, metadata);
            minEval = std::min(minEval, eval);

            //Alpha beta pruning
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

//Overidden strategy implementation
Move Level5::getStrategyImpl(Board& board, Colour colour) {
    int bestValue = INT_MIN;
    Move bestMove;

    //Get all possible moves of the current colour
    std::vector<Move> legalMoves = getAllLegalMoves(board, colour); 

    for (const auto& move : legalMoves) {

        //Simulate a move
        auto metadata = MoveSimulator::simulateMove(move, board);

        //Choose Depth 3 (can be set higher values for better moves)
        int moveValue = minimax(board, 3, false, ColourUtils::oppositeColour(colour), INT_MIN, INT_MAX);

        //Undo the move
        MoveSimulator::undoMove(move, board, metadata);

        //Update best move
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }
    //No good move found, so use level 3 strategy
    if(legalMoves.size() > 0 && bestMove == legalMoves[0]){
        return Level3::getStrategyImpl(board, colour);
    }

    return bestMove;
}
