#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "PieceFactory.h"
#include <stdexcept>

Player::Player(Colour colour, Board& board) : colour{colour}, board{board} {}

void Player::playTurn(const Move& moveRequest) {
    Move decidedMove = getMove(moveRequest);
    if (decidedMove == Move()) {
        throw std::runtime_error("Invalid move! Please choose a different position to place piece.");
    }

    //Handle pawn promotion
    char pawnPromotion = decidedMove.getPawnPromotion();
    if (pawnPromotion != ' ') {
        std::unique_ptr<Piece> piece = std::move(PieceFactory::createPiece(pawnPromotion, board));
        board.addPiece(std::move(piece), decidedMove.newPos);
        board.removePiece(decidedMove.oldPos);
    } else {
        board.movePiece(decidedMove);
    }
}
