#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <unordered_map>


class ScoreBoard {
private:
    virtual void updateScoresImpl() = 0;

protected:
    std::unordered_map<Colour, int> scores;
public:
    ScoreBoard();
    virtual ~ScoreBoard() = default;
    void updateScores();
};

#endif
