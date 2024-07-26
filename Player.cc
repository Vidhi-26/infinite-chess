#include "Player.h"

Player::Player(Colour colour, Board& board) : colour{colour}, board{board} {}

void Player::playTurn(const Move& move) {
    auto move = getMove(move);
    if (move == Move()) {
        
    } else {
        
    }
}
