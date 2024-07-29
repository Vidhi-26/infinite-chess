#include "Level1.h"
#include "../Boards/Board.h"
#include "../Moves/Move.h"
#include "StrategyUtils.h"
#include <iostream>

Level1::Level1() {}

Move Level1::getStrategyImpl(Board& board, Colour colour) {

    std::vector<Move> potentialMoves;

    for (auto it = board.cbegin(); it != board.cend(); ++it) {

        const Square& square = *it;
        if (!(square.isEmpty()) && square.piece->getColour() == colour) {
            std::vector<Move> pieceMoves = square.piece->getPossibleMoves();
            potentialMoves.insert(potentialMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return StrategyUtils::getRandomMove(potentialMoves);
}
    