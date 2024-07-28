#include "ChessGame.h"
#include <iostream>
#include "PieceFactory.h"
#include "Board.h"
#include "Move.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "SimpleScoreBoard.h"
#include "ColourUtils.h"
#include "Strategy.h"
#include "Level1.h"
#include "Level2.h"
#include <unordered_set>

// Constructor
ChessGame::ChessGame() : board(std::make_unique<Board>()), scoreboard(std::make_unique<SimpleScoreBoard>()){
    textObserver = std::move(std::make_unique<TextObserver>(board.get())); 
}

std::unique_ptr<Strategy> ChessGame::createStrategy(int level){
    if(level == 1){
        return std::make_unique<Level1>();
    }
    else{
        return std::make_unique<Level2>();
    }
}

void ChessGame::addPlayers(std::string whitePlayer, std::string blackPlayer){
    if(whitePlayer == "human"){
        auto newPlayer = std::make_unique<HumanPlayer>(Colour::WHITE, *board);
        players.push_back(std::move(newPlayer));
    }
    else if(whitePlayer.substr(0, 8) == "computer"){
        int level = stoi(whitePlayer.substr(9,1));
        auto strategy = createStrategy(level);
        strategies.push_back(std::move(strategy));
        auto newPlayer = std::make_unique<ComputerPlayer>(Colour::WHITE, *board, *strategy);
        players.push_back(std::move(newPlayer));
    }

    if(blackPlayer == "human"){
        auto newPlayer = std::make_unique<HumanPlayer>(Colour::BLACK, *board);
        players.push_back(std::move(newPlayer));
    }
    else if(blackPlayer.substr(0, 8) == "computer"){
        int level = stoi(whitePlayer.substr(9,1));
        auto strategy = createStrategy(level);
        strategies.push_back(std::move(strategy));
        auto newPlayer = std::make_unique<ComputerPlayer>(Colour::BLACK, *board, *strategy);
        players.push_back(std::move(newPlayer));
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
    if(curState == GameState::BLACK_WINS || curState == GameState::WHITE_WINS || curState == GameState::DRAW){
        scoreboard->updateScores(ColourUtils::getWinner(curState));
        board->reset();
    }
    else if(curState == GameState::BLACK_IN_CHECK){
        std::cout << "Black in check" << std::endl;
    }
    else if(curState == GameState::WHITE_IN_CHECK){
        std::cout << "White in check" << std::endl;
    }
    board->render();
}

// Method to move a piece from loc1 to loc2
// TODO: Make pawnPromotion char
void ChessGame::movePiece(std::string loc1, std::string loc2, char pawnPromotion) {
    auto l1 = getLocation(loc1);
    auto l2 = getLocation(loc2);
    
    Move newMove{l1.first, l1.second, l2.first, l2.second};

    // Input validation
    if (board->isEmptyPosition(newMove.oldPos.first, newMove.oldPos.second)){
        std::cout<<"No piece exists there"<<std::endl;
        return;
    } else if (turn != board->getPieceAt(newMove.oldPos.first, newMove.oldPos.second).getColour()) {
        std::cout<<"It is not your turn! Pass to next player" << std::endl;
        return;
    }

    // Check for pawn promotion
    if(pawnPromotion != ' '){
        // Input validation for pawn promotion
        std::unordered_set<char> validPromotions{'q', 'r', 'b', 'n'};
        if (turn == Colour::WHITE) {
            if (!isupper(pawnPromotion) || validPromotions.find(tolower(pawnPromotion)) == validPromotions.end()) {
                std::cout << "Invalid input. Cannot promote to " << pawnPromotion << std::endl;
                return;
            }
        } else if (turn == Colour::BLACK) {
            if (validPromotions.find(tolower(pawnPromotion)) == validPromotions.end()) {
                std::cout << "Inavlid input. Cannot promote to " << pawnPromotion << std::endl;
                return;
            }
        }

        // Check if pawn promotion applies to requested move
        Piece& piece = board->getPieceAt(newMove.oldPos.first, newMove.oldPos.second);
        if (dynamic_cast<const Pawn*>(&piece) == nullptr) {     // Not a pawn
            std::cout << "Pawn promotion does not apply. Try again!" << std::endl;
            return;
        }

        bool isValidPawnMove = (turn == Colour::WHITE && newMove.oldPos.first == 6 && newMove.newPos.first == 7) ||
                               (turn == Colour::BLACK && newMove.oldPos.first == 1 && newMove.newPos.first == 0);
        if (!isValidPawnMove) {
            std::cout << "Pawn promotion does not apply. Try again!" << std::endl;
            return;
        }

        newMove.addPawnPromotion(pawnPromotion);
    }

    try{
        if(turn == Colour::WHITE){
            players[0]->playTurn(newMove);
        } else {
            players[1]->playTurn(newMove);
        }
        postMoveAction();
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
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
    std::unique_ptr<Piece> piece = std::move(PieceFactory::createPiece(key[0], *board));
    if (piece) {
        (*board).addPiece(std::move(piece), getLocation(loc));
    }
}

// Method to remove a piece from the board
void ChessGame::removePiece(std::string loc) {
    (*board).removePiece(getLocation(loc));   
}

// Method to check if the board configuration is valid
bool ChessGame::isBoardConfigValid() {
    return board->isValidConfig();
}
