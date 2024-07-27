#include "Player.h"
#include "Board.h"
#include "Move.h"
#include <stdexcept>

Player::Player(Colour colour, Board& board) : colour{colour}, board{board} {}

void Player::playTurn(const Move& moveRequest) {
    Move decidedMove = getMove(moveRequest);
    if (decidedMove == Move()) {
        throw std::runtime_error("Invalid move! Please choose a different position to place piece.");
    }
    board.movePiece(decidedMove);
}
