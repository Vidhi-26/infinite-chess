#include "SimpleScoreBoard.h"

SimpleScoreBoard::SimpleScoreBoard() : ScoreBoard{} {
    scores[Colour::WHITE] = 0;
    scores[Colour::BLACK] = 0;
}

void SimpleScoreBoard::updateScoresImpl(Colour colour) {
    scores[colour]++;
}

void SimpleScoreBoard::updateScoresImpl(Colour colour, double points) {
    scores[colour] += points;
}
