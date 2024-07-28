#include "PieceFactory.h"

std::unique_ptr<Piece> PieceFactory::createPiece(char key, Board& board) {
    if (key == 'R') {
        return std::make_unique<Rook>(Colour::WHITE, board);
    } else if (key == 'N') {
        return std::make_unique<Knight>(Colour::WHITE, board);
    } else if (key == 'B') {
        return std::make_unique<Bishop>(Colour::WHITE, board);
    } else if (key == 'Q') {
        return std::make_unique<Queen>(Colour::WHITE, board);
    } else if (key == 'K') {
        return std::make_unique<King>(Colour::WHITE, board);
    } else if (key == 'P') {
        return std::make_unique<Pawn>(Colour::WHITE, board);
    } else if (key == 'r') {
        return std::make_unique<Rook>(Colour::BLACK, board);
    } else if (key == 'n') {
        return std::make_unique<Knight>(Colour::BLACK, board);
    } else if (key == 'b') {
        return std::make_unique<Bishop>(Colour::BLACK, board);
    } else if (key == 'q') {
        return std::make_unique<Queen>(Colour::BLACK, board);
    } else if (key == 'k') {
        return std::make_unique<King>(Colour::BLACK, board);
    } else if (key == 'p') {
        return std::make_unique<Pawn>(Colour::BLACK, board);
    }
    return nullptr;
}
