#ifndef CHESSGAME_H
#define CHESSGAME_H
#include "./Boards/Board.h"
#include "./Players/Player.h"
#include "./ScoreBoards/ScoreBoard.h"
#include <vector>
#include "./Strategies/Strategy.h"
#include "./Observers/TextObserver.h"
#include "./Observers/GraphicalObserver.h"

class ChessGame {
private:
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ScoreBoard> scoreboard;
    std::unique_ptr<TextObserver> textObserver;
    std::unique_ptr<GraphicalObserver> graphicalObserver;
    Colour turn;
    std::vector<std::unique_ptr<Strategy>> strategies;
    std::unique_ptr<Strategy> createStrategy(int level);
    void postMoveAction(Move);
    void createPlayer(std::string, Colour);
public:
    ChessGame();
    virtual ~ChessGame() = default;
    void movePiece(std::string loc1, std::string loc2, char pawnPromotion = ' ');
    void movePiece();
    void addPlayers(std::string player1, std::string player2);
    void acceptResignation();
    void setTurn(std::string);
    bool addPiece(std::string piece, std::string loc);
    bool removePiece(std::string loc);
    bool isBoardConfigValid();
    void displayBoard();
};

#endif
