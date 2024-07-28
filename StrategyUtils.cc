#include "StrategyUtils.h"
#include <random>
#include <chrono>
#include <algorithm>

Move StrategyUtils::getRandomMove(std::vector<Move> moves){
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};

	for (int i = 0; i < 10; i++) {
		std::shuffle(moves.begin(), moves.end(), rng);
	}
    return moves.front();
}