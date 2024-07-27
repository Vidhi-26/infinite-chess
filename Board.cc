#include "Board.h"
#include "Move.h"

Board::Board(int rowSize, int colSize) : pieces(rowSize, std::vector<std::unique_ptr<Piece>>(colSize)){}

std::pair<int, int> Board::getPositionOfPiece(const Piece& piece) const {
    for (size_t r = 0; r < pieces.size(); r++) {
        for (size_t c = 0; c < pieces[r].size(); c++) {
            if (pieces[r][c].get() == &piece) {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

Piece& Board::getPieceAt(int r, int c) const {
    return *pieces[r][c].get();
}

bool Board::isValidPosition(int r, int c) const {
    return r >= 0 && r < pieces.size() && c >= 0 && c < pieces[r].size();
}

bool Board::isEmptyPosition(int r, int c) const {
    return nullptr == pieces[r][c].get();
}

void Board::movePiece(const Move& move) {
    grid[move.newPos.first][move.newPos.second]->piece = grid[move.oldPos.first][move.oldPos.second]->piece;
    grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;
}
