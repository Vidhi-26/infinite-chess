#include "Rook.h"

Rook::Rook(Colour colour, Board& board): Piece{colour, board}{
    
}
std::vector<Move> Rook::getPossibleMovesImpl() const{
    return {};
}