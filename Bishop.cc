#include "Bishop.h"
#include "Board.h"
#include "Move.h"

// Calls superclass ctor - points default value for Bishop is 3
Bishop::Bishop(Colour colour, Board& board, int points) : Piece{colour, board, points} {}

// Private implementation method for getPossibleMoves(). 
// Returns customized Bishop moves, that is Bishop moves diagonally unless a piece blocks its path
std::vector<Move> Bishop::getPossibleMovesImpl() const {
    std::vector<Move> possibleMoves;
    std::vector<std::pair<int, int>> dirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};   // Diagonal directions

    // Begin from current position on board
    auto curPos = board.getPositionOfPiece(*this);
    int r = curPos.first, c = curPos.second;

    // Check in all diagonal directions
    for (const auto& dir : dirs) {
        int nr = r, nc = c;
        
        // Keep moving until it reached out of board or another piece blocks it
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
