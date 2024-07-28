#include "Pawn.h"
#include "Board.h"
#include "Move.h"
#include <cctype>

Pawn::Pawn(Colour colour, Board& board, int points) : Piece{colour, board, points} {}

std::vector<Move> Pawn::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<int> captureDirs = {1, -1};

    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    int direction = (this->colour == Colour::WHITE) ? 1 : -1; // Pawns move forward
    int startRow = (this->colour == Colour::WHITE) ? 1 : 6; // Starting row for white and black pawns
    int endRow = (this->colour == Colour::WHITE) ? 7 : 0;  // Ending row for pawn promotion

    // Move forward by one square
    if (board.isValidPosition(r + direction, c) && board.isEmptyPosition(r + direction, c)) {
        possibleMoves.emplace_back(r, c, r + direction, c);
        
        // Add pawn promotion
        if (r + direction == endRow) {
            for (const auto& pp : pawnPromotions) {
                possibleMoves.emplace_back(r, c, endRow, c, (this->colour == Colour::WHITE) ? toupper(pp) : tolower(pp));
            }
        }
        
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

            // Add pawn promotion
            if (nr == endRow) {
                for (const auto& pp : pawnPromotions) {
                    possibleMoves.emplace_back(r, c, endRow, nc, (this->colour == Colour::WHITE) ? toupper(pp) : tolower(pp));
                }
            }
        }
    }

    return possibleMoves;
}

char Pawn::getCodeImpl() const{
    return 'p';
}
