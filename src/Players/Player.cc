#include "Player.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"
#include "../Pieces/PieceFactory.h"
#include <stdexcept>
#include <iostream>

Player::Player(Colour colour, Board& board) : colour{colour}, board{board} {}

Move Player::playTurn(const Move& moveRequest) {
    
    Move decidedMove = getMove(moveRequest);
    if (decidedMove == Move()) {
        throw std::runtime_error("Invalid move! Please choose a different position to place piece.");
    }

    char pawnPromotion = decidedMove.getPawnPromotion();
    if (pawnPromotion == 'e') {             // En passante
        board.movePiece(decidedMove);
        board.removePiece({decidedMove.oldPos.first, decidedMove.newPos.second});
    } else if (pawnPromotion != ' ') {      // Pawn promotion
        std::unique_ptr<Piece> piece = std::move(PieceFactory::createPiece(pawnPromotion, board));
        board.addPiece(std::move(piece), decidedMove.newPos);
        board.removePiece(decidedMove.oldPos);
    } else {                                // Normal case
        board.movePiece(decidedMove);
    }

    return decidedMove;
}
