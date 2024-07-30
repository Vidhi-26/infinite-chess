#include "King.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"
#include "Rook.h"
#include <iostream>

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

    // Add castling moves
    if (curPos == getInitialPosition() && !hasPieceMoved(getInitialPosition())) {
        // Castling king-side
        if (canCastleKingSide()) {
            possibleMoves.emplace_back(r, c, r, c + 2, 'c');
        }
        // Castling queen-side
        if (canCastleQueenSide()) {
            possibleMoves.emplace_back(r, c, r, c - 2, 'c');
        }
    }

    return possibleMoves;
}

char King::getCodeImpl() const{
    return 'k';
}

// Helpers for castling
std::pair<int, int> King::getInitialPosition() const {
    return this->colour == Colour::WHITE ? std::make_pair(0, 4) : std::make_pair(7, 4);
}

bool King::canCastleKingSide() const {
    auto curPos = getInitialPosition();
    int r = curPos.first, c = curPos.second;

    if (board.isEmptyPosition(r, c + 1) && board.isEmptyPosition(r, c + 2)) {
        if (!board.isPositionUnderAttack(r, c, this->colour) &&
            !board.isPositionUnderAttack(r, c + 1, this->colour) &&
            !board.isPositionUnderAttack(r, c + 2, this->colour) && 
            !board.isEmptyPosition(r, c + 3)) {
            auto rook = dynamic_cast<const Rook*>(&board.getPieceAt(r, c + 3));
            if (rook != nullptr && !hasPieceMoved(std::make_pair(r, c + 3))) {
                return true;
            }
        }
    }
    return false;
}

bool King::canCastleQueenSide() const {
    auto curPos = getInitialPosition();
    int r = curPos.first, c = curPos.second;

    if (board.isEmptyPosition(r, c - 1) && board.isEmptyPosition(r, c - 2) && board.isEmptyPosition(r, c - 3)) {
        if (!board.isPositionUnderAttack(r, c, this->colour) &&
            !board.isPositionUnderAttack(r, c - 1, colour) &&
            !board.isPositionUnderAttack(r, c - 2, colour) &&
            !board.isEmptyPosition(r, c - 4)) {
            auto rook = dynamic_cast<const Rook*>(&board.getPieceAt(r, c - 4));
            if (rook != nullptr && !hasPieceMoved(std::make_pair(r, c - 4))) {
                return true;
            }
        }
    }
    return false;
}
