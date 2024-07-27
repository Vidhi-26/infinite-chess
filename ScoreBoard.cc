#include "ScoreBoard.h"
#include "ColourUtils.h"
#include <iostream>

ScoreBoard::ScoreBoard() {}

void ScoreBoard::updateScores(Colour colour) {
    updateScoresImpl(colour);
    displayScores();
}

void ScoreBoard::displayScores() {
    std::cout << "Final score:" << std::endl;
    for (const auto& score : scores) {
        std::cout << ColourUtils::toString(score.first) << ": " << score.second << std::endl;
    }
}
