#include "Piece.h"

Piece::Piece(Colour colour, Board& board) : colour{colour}, board{board};

std::vector<Move> Piece::getPossibleMoves() const {
    return getPossibleMovesImpl();
}
