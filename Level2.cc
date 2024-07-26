#include "Level2.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"
#include <unordered_map>

Move Level2::getStrategyImpl(const Board& board, Colour colour) const{
    Move bestMove{};
    for(auto it = board.cbegin(); it!= board.cend(); ++it){
        const Piece& piece = *it;
        std::vector<Move> moves = piece.getPossibleMoves();
        
        for(auto& move: moves){
            Piece& enemy= board.getPieceAt(move.newPos.first, move.newPos.second);
            if(enemy.getColour() != colour && enemy.getPoints() > bestMove.second){
                bestMove = {&move, enemy.getPoints()};
            }
        }
    }
    if(!bestMove.first) return Level1::getStrategyImpl(board, colour);
    return *bestMove.first;
}