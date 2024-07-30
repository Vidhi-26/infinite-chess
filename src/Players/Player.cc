#include "Player.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"
#include "../Pieces/PieceFactory.h"
#include "../Moves/MoveSimulator.h"
#include <stdexcept>
#include <iostream>

Player::Player(Colour colour, Board& board) : colour{colour}, board{board} {}

Move Player::playTurn(const Move& moveRequest) {
    
    Move decidedMove = getMove(moveRequest);
    if (decidedMove == Move()) {
        throw std::runtime_error("Invalid move! Please choose a different position to place piece.");
    }

    auto newMetaData = MoveSimulator::simulateMove(decidedMove, board);
    board.addToMoveHistory(decidedMove, newMetaData);

    return decidedMove;
}
