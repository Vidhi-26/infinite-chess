#include "Knight.h"
#include "Board.h"
#include "Move.h"

Knight::Knight(Colour colour, Board& board) : Piece{colour, board} {}

std::vector<Move> Knight::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    for (const auto& dir : dirs) {
        int nr = r + dir.first;
        int nc = c + dir.second;

        if (board.isValidPosition(nr, nc)) {
            if (board.isEmptyPosition(nr, nc) || board.getPieceAt(nr, nc).colour != this->colour) {
                possibleMoves.emplace_back(r, c, nr, nc);
            }
        }
    }

    return possibleMoves;
}
