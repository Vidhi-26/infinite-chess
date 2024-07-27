#include "Level1.h"
#include "Board.h"
#include "Move.h"
#include <random>
#include <chrono>
#include <algorithm>

Level1::Level1() {}

Move Level1::getStrategyImpl(const Board& board, Colour colour) const {
    std::vector<Move> potentialMoves;

    for (auto it = board.cbegin(); it != board.cend(); ++it) {
        const Square& square = *it;
        if (!(square.isEmpty())) {
            std::vector<Move> pieceMoves = square.piece->getPossibleMoves();
            potentialMoves.insert(potentialMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};

	for (int i = 0; i < 10; i++) {
		std::shuffle(potentialMoves.begin(), potentialMoves.end(), rng);
	}

    return potentialMoves.front();
}
