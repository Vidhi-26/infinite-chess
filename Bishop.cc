#include "Bishop.h"
#include "Board.h"
#include "Move.h"

Bishop::Bishop(Colour colour, Board& board) : Piece{colour, board} {}

std::vector<Move> Bishop::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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
                    if (board.getPieceAt(nr, nc).getColour() != this->colour) {  // it is possible to capture opponent piece
                        possibleMoves.emplace_back(r, c, nr, nc);
                    }
                    break;  // another piece blocks path
                }
            } else {
                break;  // out of bounds on board
            }
        }
    }

    return possibleMoves;
}
