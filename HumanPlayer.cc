#include "HumanPlayer.h"
#include "Piece.h"
#include "Board.h"
#include <unordered_set>

HumanPlayer::HumanPlayer(Colour colour, Board& board) : Player{colour, board} {}

Move HumanPlayer::getMove(const Move& move) const {
    Piece& piece = board.getPieceAt(move.oldPos.first, move.oldPos.second);

    std::vector<Move> possibleMoves = piece.getPossibleMoves();
    std::unordered_set<Move> possibleMovesSet(possibleMoves.begin(), possibleMoves.end());
    
    return possibleMovesSet.find(move) != possibleMovesSet.end() ? move : Move();
}
