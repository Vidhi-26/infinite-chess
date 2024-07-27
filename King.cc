#include "King.h"
#include "Board.h"
#include "Move.h"

King::King(Colour colour, Board& board, int points) : Piece{colour, board, points} {}

std::vector<Move> King::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}, // horizontal and vertical directions
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // diagonal directions
    };

    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    for (const auto& dir : dirs) {
        int nr = r + dir.first;
        int nc = c + dir.second;

        if (board.isValidPosition(nr, nc)) {
            if (board.isEmptyPosition(nr, nc) || board.getPieceAt(nr, nc).getColour() != this->colour) {
                possibleMoves.emplace_back(r, c, nr, nc);
            }
        }
    }

    return possibleMoves;
}
