#include "ChessGame.h"
#include <iostream>
#include "Rook.h"
#include "Board.h"

// Constructor
ChessGame::ChessGame() : board(std::make_unique<Board>()), scoreboard(std::make_unique<ScoreBoard>()) {
    players.push_back(std::make_unique<Player>(Colour::WHITE));
    players.push_back(std::make_unique<Player>(Colour::BLACK));
    turn = Colour::WHITE;
}

// Method to move a piece from loc1 to loc2
void ChessGame::movePiece(std::string loc1, std::string loc2) {
    if (board->movePiece(loc1, loc2, turn)) {
        // Toggle turn
        turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    } else {
        std::cerr << "Invalid move from " << loc1 << " to " << loc2 << std::endl;
    }
}

// Method to accept resignation
void ChessGame::acceptResignation() {
    std::cout << ((turn == Colour::WHITE) ? "Black" : "White") << " wins by resignation." << std::endl;
}

// Method to set the turn
void ChessGame::setTurn(std::string player) {
    turn = (player == "white") ? Colour::WHITE : Colour::BLACK;
}

// Method to add a piece to the board
void ChessGame::addPiece(std::string piece, std::string loc) {
    if(piece == "R"){
        std::unique_ptr<Rook>
    }
    else if(piece == "N"){

    }
    else if(piece == "B"){

    }
    else if(piece == "Q"){

    }
    else if(piece == "K"){

    }
    else if(piece == "P"){
        
    }

    else if(piece == "r"){

    }
    else if(piece == "n"){

    }
    else if(piece == "b"){

    }
    else if(piece == "q"){

    }
    else if(piece == "k"){

    }
    else if(piece == "p"){
        
    }
}

// Method to remove a piece from the board
void ChessGame::removePiece(std::string loc) {
    
}

// Method to check if the board configuration is valid
bool ChessGame::isBoardConfigValid() {
    return board->isValidConfig();
}

