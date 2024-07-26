#include "Level2.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"

Move Level2::getStrategyImpl(const Board& board, Colour colour) const{
    for(auto it = board.cbegin(); it!= board.cend(); ++it){
        const Piece& piece = *it;
        auto moves = piece.getPossibleMoves();
        
    }
    return Level1::getStrategyImpl(board, colour);
}