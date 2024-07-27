#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <unordered_map>
#include "Colour.h"

class ScoreBoard {
private:
    virtual void updateScoresImpl(Colour) = 0;

protected:
    std::unordered_map<Colour, int> scores;

public:
    ScoreBoard();
    virtual ~ScoreBoard() = default;
    void updateScores(Colour);
    void displayScores();
};

#endif
