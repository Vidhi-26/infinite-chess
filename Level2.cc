#include "Level2.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"
#include <unordered_map>

Level2::Level2() {}

Move Level2::getStrategyImpl(const Board& board, Colour colour) const{
    //Keep track of the best move (categorized by most points acquired by capturing)
    Move bestMove{}; 
    int bestScore = -1;

    //Iterate over all the board pieces and check which enemy to capture
    for(auto it = board.cbegin(); it != board.cend(); ++it){
        const Square& square = *it;
        if(square.isEmpty()) continue;
        
        auto piece = square.piece;
        if(piece->getColour() != colour) continue;
        std::vector<Move> moves = piece->getPossibleMoves();

        //Iterate through each possible move of the current piece
        for(auto& move: moves){
            
            //Check if there is a piece
            if(board.isEmptyPosition(move.newPos.first, move.newPos.second)) continue;
            Piece& enemy= board.getPieceAt(move.newPos.first, move.newPos.second);
            
            //Check if it is an enemy piece and if it has more points
            if(enemy.getColour() != colour && enemy.getPoints() > bestScore){

                //Update best move
                bestMove = move;
                bestScore = enemy.getPoints();
            }
        }
    }

    //If no move found that can capture, then use level 1 strategy
    if(bestMove.newPos.first == -1 || bestMove.newPos.second == -1) return Level1::getStrategyImpl(board, colour);
    return bestMove;
}
