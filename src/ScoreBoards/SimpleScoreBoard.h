#ifndef SIMPLESCOREBOARD_H
#define SIMPLESCOREBOARD_H
#include "ScoreBoard.h"

class SimpleScoreBoard : public ScoreBoard {
private:
    void updateScoresImpl(Colour);
    void updateScoresImpl(Colour, double);

public:
    SimpleScoreBoard();
    ~SimpleScoreBoard() = default; 
};

#endif
