#include "Rook.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"

Rook::Rook(Colour colour, Board& board, int points) : Piece{colour, board, points} {}

std::vector<Move> Rook::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1} // Horizontal and vertical directions
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

char Rook::getCodeImpl() const{
    return 'r';
}
