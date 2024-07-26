#include "Queen.h"
#include "Board.h"
#include "Move.h"

Queen::Queen(Colour colour, Board& board) : Piece{colour, board} {}

std::vector<Move> Queen::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}, // horizontal and vertical directions
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // diagonal directions
    };

    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    for (const auto& dir : dirs) {
        int nr = r, nc = c;

        while (true) {
            nr += dir.first;
            nc += dir.second;

            if (board.isValidPosition(nr, nc)) {
                if (board.isEmptyPosition(nr, nc)) {
                    possibleMoves.emplace_back(r, c, nr, nc);
                } else {
                    if (board.getPieceAt(nr, nc).getColour() != this->colour) {
                        possibleMoves.emplace_back(r, c, nr, nc);
                    }
                    break;
                }
            } else {
                break;
            }
        }
    }

    return possibleMoves;
}    
