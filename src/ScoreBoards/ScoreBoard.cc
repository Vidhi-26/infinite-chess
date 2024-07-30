#include "ScoreBoard.h"
#include "../ColourUtils.h"
#include <iostream>
#include <iomanip>

ScoreBoard::ScoreBoard() {}

void ScoreBoard::updateScores(Colour colour) {
    // Handle draw
    if (colour == Colour::DRAW) {
        for (auto& score : scores) {
            updateScoresImpl(score.first, 0.5);
        }
    } else {
        // Customizable update scores
        updateScoresImpl(colour);
    }

    // Display scores flexible for observers
    displayScores();
}

void ScoreBoard::displayScores() {
    std::cout << "Final score:" << std::endl;
    for (const auto& score : scores) {
        std::cout << ColourUtils::toString(score.first) << ": "
                  << std::fixed << std::setprecision(1) << score.second 
                  << std::endl;
    }
}
