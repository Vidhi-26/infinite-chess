#include "Pawn.h"

Pawn::Pawn(Colour colour, Board& board): Piece{colour, board}{

}
std::vector<Move> Pawn::getPossibleMovesImpl() const{
    return {};
}