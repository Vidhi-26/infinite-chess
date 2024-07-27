#include "ChessGame.h"
#include <iostream>
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Board.h"
#include "Move.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "SimpleScoreBoard.h"

// Constructor
ChessGame::ChessGame() : board(std::make_unique<Board>()), scoreboard(std::make_unique<SimpleScoreBoard>()) {}

void ChessGame::addPlayers(std::string whitePlayer, std::string blackPlayer){
    if(whitePlayer == "human"){
        players.push_back(std::make_unique<HumanPlayer>(Colour::WHITE, board));
    }
    else if(whitePlayer.substr(0, 8) == "computer"){
        int level = stoi(whitePlayer.substr(9,1));
        players.push_back(std::make_unique<ComputerPlayer>(Colour::WHITE, board, level));
    }

    if(blackPlayer == "human"){
        players.push_back(std::make_unique<HumanPlayer>(Colour::BLACK, board));
    }
    else if(blackPlayer.substr(0, 8) == "computer"){
        int level = stoi(whitePlayer.substr(9,1));
        players.push_back(std::make_unique<ComputerPlayer>(Colour::BLACK, board, level));
    }
   
    turn = Colour::WHITE;
}

std::pair<int,int> getLocation(std::string loc){
    return {loc[1] - '1', loc[0] - 'a'};
}

void ChessGame::postMoveAction(){
    turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    board->updateGameState(turn);
    GameState curState = board->getGameState();
    // TODO: Make a switch statement, and return Color from GameState to scoreboard
    // Use ColorUtils!
    if(curState == GameState::BLACK_WINS || curState == GameState::WHITE_WINS || curState == GameState::DRAW){
        scoreboard->updateScores(curState);
        board->reset();
    }
    else if(curState == GameState::BLACK_IN_CHECK){
        //Display to screen
    }
    else if(curState == GameState::WHITE_IN_CHECK){
        //Display to screen
    }
    else{
        board->render();
    }
}

// Method to move a piece from loc1 to loc2
// TODO: Make pawnPromotion char
void ChessGame::movePiece(std::string loc1, std::string loc2, std::string pawnPromotion) {
    auto l1 = getLocation(loc1);
    auto l2 = getLocation(loc2);
    Move newMove{l1.first, l1.second, l2.first, l2.second};
    if(pawnPromotion != ""){
        newMove.addPawnPromotion(pawnPromotion[0]);
    }
    if(turn == Colour::WHITE){
        players[0]->playTurn(newMove);
    }
    else players[1]->playTurn(newMove);
    postMoveAction();
}

void ChessGame::movePiece(){
    if(turn == Colour::WHITE){
        players[0]->playTurn();
    }
    else players[1]->playTurn();
    postMoveAction();
}

// Method to accept resignation
void ChessGame::acceptResignation() {
    std::cout << ((turn == Colour::WHITE) ? "Black" : "White") << " wins by resignation." << std::endl;
}

// Method to set the turn
void ChessGame::setTurn(std::string colour) {
    turn = (colour == "white") ? Colour::WHITE : Colour::BLACK;
}

// Method to add a piece to the board
void ChessGame::addPiece(std::string key, std::string loc) {
    std::unique_ptr<Piece> piece;
    if(key == "R"){
        piece = std::make_unique<Rook>(Colour::WHITE, board);
    }
    else if(key == "N"){
        piece = std::make_unique<Knight>(Colour::WHITE, board);
    }
    else if(key == "B"){
        piece = std::make_unique<Bishop>(Colour::WHITE, board);
    }
    else if(key == "Q"){
       piece = std::make_unique<Queen>(Colour::WHITE, board);
    }
    else if(key == "K"){
        piece = std::make_unique<King>(Colour::WHITE, board);
    }
    else if(key == "P"){
        piece = std::make_unique<Pawn>(Colour::WHITE, board);
    }
    else if(key == "r"){
        piece = std::make_unique<Rook>(Colour::BLACK, board);
    }
    else if(key == "n"){
        piece = std::make_unique<Knight>(Colour::BLACK, board);
    }
    else if(key == "b"){
        piece = std::make_unique<Bishop>(Colour::BLACK, board);
    }
    else if(key == "q"){
        piece = std::make_unique<Queen>(Colour::BLACK, board);
    }
    else if(key == "k"){
        piece = std::make_unique<King>(Colour::BLACK, board);
    }
    else if(key == "p"){
        piece = std::make_unique<Pawn>(Colour::BLACK, board);
    }
    (*board).addPiece(std::move(piece), getLocation(loc));
}

// Method to remove a piece from the board
void ChessGame::removePiece(std::string loc) {
    (*board).removePiece(getLocation(loc));   
}

// Method to check if the board configuration is valid
bool ChessGame::isBoardConfigValid() {
    return board->isValidConfig();
}

