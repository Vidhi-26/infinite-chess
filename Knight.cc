#include "Knight.h"

Knight::Knight(Colour colour, Board& board): Piece{colour, board}{
    
}
std::vector<Move> Knight::getPossibleMovesImpl() const{
    return {};
}