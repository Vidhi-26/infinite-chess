#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState {
    WHITE_WINS,
    BLACK_WINS,
    DRAW,
    IN_PROGRESS,
    WHITE_IN_CHECK,
    BLACK_IN_CHECK,
    SETUP
};

#endif
