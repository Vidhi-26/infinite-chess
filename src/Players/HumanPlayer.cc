#include "HumanPlayer.h"
#include "../Pieces/Piece.h"
#include "../Boards/Board.h"
// #include <set>

HumanPlayer::HumanPlayer(Colour colour, Board& board) : Player{colour, board} {}

Move HumanPlayer::getMove(const Move& move) const {
    Piece& piece = board.getPieceAt(move.oldPos.first, move.oldPos.second);

    std::vector<Move> possibleMoves = piece.getPossibleMoves();

    // std::set<Move> possibleMovesSet(possibleMoves.begin(), possibleMoves.end());
    // return possibleMovesSet.find(move) != possibleMovesSet.end() ? move : Move();

    for (const auto& possibleMove : possibleMoves) {
        if (possibleMove == move) {
            return move;
        }
    }
    return Move();
}
