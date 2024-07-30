#include "Level2.h"
#include "../Boards/Board.h"
#include "../Pieces/Piece.h"
#include "../Colour.h"
#include "../Moves/Move.h"
#include "StrategyUtils.h"
#include <unordered_map>

Level2::Level2() {}

Move Level2::getStrategyImpl(Board& board, Colour colour) {

    std::vector<Move> possibleBestMoves;
    
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
            if(board.isEmptyPosition(move.newPos.first, move.newPos.second)) {

                //Simulate a move
                board.movePiece(move);
                if(board.isKingInCheck(colour == Colour::BLACK ? Colour::WHITE : Colour::BLACK)){
                    possibleBestMoves.push_back(move);
                }
                //Revert
                board.movePiece(Move(move.newPos, move.oldPos));
            }
            else{
                Piece& enemy= board.getPieceAt(move.newPos.first, move.newPos.second);

                //Check if it is an enemy piece
                if(enemy.getColour() != colour){
                    possibleBestMoves.push_back(move);
                }
            }

        }
    }

    //If no move found that can capture, then use level 1 strategy
    if(possibleBestMoves.size() == 0) return Level1::getStrategyImpl(board, colour);

    //If not, randomly choose from the current best moves
    return StrategyUtils::getRandomMove(possibleBestMoves);
}
