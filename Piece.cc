#include "Piece.h"

Piece::Piece(Colour colour, const Board& board, int points) : colour{colour}, board{board}, points{points} {}

std::vector<Move> Piece::getPossibleMoves() const {
    return getPossibleMovesImpl();
}

Colour Piece::getColour() const {
    return colour;
}
