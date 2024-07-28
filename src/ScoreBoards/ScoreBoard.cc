#include "ScoreBoard.h"
#include "../ColourUtils.h"
#include <iostream>

ScoreBoard::ScoreBoard() {}

void ScoreBoard::updateScores(Colour colour) {
    // Handle draw
    if (colour == Colour::DRAW) {
        for (auto& score : scores) {
            updateScoresImpl(score.first);
        }
    }
    
    // Customizable update scores
    updateScoresImpl(colour);

    // Display scores flexible for observers
    displayScores();
}

void ScoreBoard::displayScores() {
    std::cout << "Final score:" << std::endl;
    for (const auto& score : scores) {
        std::cout << ColourUtils::toString(score.first) << ": " << score.second << std::endl;
    }
}
