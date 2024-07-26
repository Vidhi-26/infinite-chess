#include "Pawn.h"
#include "Board.h"
#include "Move.h"

Pawn::Pawn(Colour colour, Board& board) : Piece{colour, board} {}

std::vector<Move> Pawn::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<int> captureDirs = {1, -1};

    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    int direction = (this->colour == Colour::WHITE) ? 1 : -1; // Pawns move forward
    int startRow = (this->colour == Colour::WHITE) ? 1 : 6; // Starting row for white and black pawns

    // Move forward by one square
    if (board.isValidPosition(r + direction, c) && board.isEmptyPosition(r + direction, c)) {
        possibleMoves.emplace_back(r, c, r + direction, c);
        
        // Move forward by two squares from the starting position
        if (r == startRow && board.isEmptyPosition(r + 2 * direction, c)) {
            possibleMoves.emplace_back(r, c, r + 2 * direction, c);
        }
    }

    // Capture diagonally
    for (int colDir : captureDirs) {
        int nr = r + direction;
        int nc = c + colDir;

        if (board.isValidPosition(nr, nc) && 
            !board.isEmptyPosition(nr, nc) && 
            board.getPieceAt(nr, nc).getColour() != this->colour) {
            possibleMoves.emplace_back(r, c, nr, nc);
        }
    }

    return possibleMoves;
}
