#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "Board.h"
#include "Player.h"
#include "ScoreBoard.h"
#include <vector>
#include "Strategy.h"
#include "TextObserver.h"

class ChessGame {
private:
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ScoreBoard> scoreboard;
    std::unique_ptr<TextObserver> textObserver;
    Colour turn;
    std::vector<std::unique_ptr<Strategy>> strategies;
    std::unique_ptr<Strategy> createStrategy(int level);
    void postMoveAction();
    void createPlayer(std::string, Colour);
public:
    ChessGame();
    virtual ~ChessGame() = default;
    void movePiece(std::string loc1, std::string loc2, char pawnPromotion = ' ');
    void movePiece();
    void addPlayers(std::string player1, std::string player2);
    void acceptResignation();
    void setTurn(std::string);
    void addPiece(std::string piece, std::string loc);
    void removePiece(std::string loc);
    bool isBoardConfigValid();
};

#endif
