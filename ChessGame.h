#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "Board.h"
#include "Player.h"
#include "ScoreBoard.h"
#include <vector>

class ChessGame {
private:
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ScoreBoard> scoreboard;
    Colour turn;
public:
    ChessGame();
    virtual ~ChessGame() = default;
    void movePiece(std::string loc1, std::string loc2);
    void acceptResignation();
    void setTurn(std::string);
    void addPiece(std::string piece, std::string loc);
    void removePiece(std::string loc);
    bool isBoardConfigValid();
};

#endif
