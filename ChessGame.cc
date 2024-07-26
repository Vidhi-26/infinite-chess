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

// Constructor
ChessGame::ChessGame() : board(std::make_unique<Board>()), scoreboard(std::make_unique<ScoreBoard>()) {
   
}

void ChessGame::addPlayers(std::string player1, std::string player2){
    players.push_back(std::make_unique<Player>(Colour::WHITE));
    players.push_back(std::make_unique<Player>(Colour::BLACK));
    turn = Colour::WHITE;
}

std::pair<int,int> getLocation(std::string loc){
    return {loc[1] - '1', loc[0] - 'a'};
}

// Method to move a piece from loc1 to loc2
void ChessGame::movePiece(std::string loc1, std::string loc2) {
    auto l1 = getLocation(loc1);
    auto l2 = getLocation(loc2);
    Move newMove{l1.first, l1.second, l2.first, l2.second};

    if(turn == Colour::WHITE){
        players[0]->playTurn(newMove);
    }
    else players[1]->playTurn(newMove);
    
    turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}

void ChessGame::movePiece(){
    if(turn == Colour::WHITE){
        players[0]->playTurn();
    }
    else players[1]->playTurn();
    
    turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
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
    (*board).addPiece(std::move(piece));
}

// Method to remove a piece from the board
void ChessGame::removePiece(std::string loc) {
    (*board).removePiece(getLocation(loc));   
}

// Method to check if the board configuration is valid
bool ChessGame::isBoardConfigValid() {
    return board->isValidConfig();
}

