#include "ChessGame.h"
#include <iostream>
#include "./Pieces/PieceFactory.h"
#include "./Boards/Board.h"
#include "./Moves/Move.h"
#include "./Players/HumanPlayer.h"
#include "./Players/ComputerPlayer.h"
#include "./ScoreBoards/SimpleScoreBoard.h"
#include "ColourUtils.h"
#include "./Strategies/Strategy.h"
#include "./Strategies/Level1.h"
#include "./Strategies/Level2.h"
#include "./Strategies/Level3.h"
#include "./Strategies/Level4.h"
#include <unordered_set>

// Constructor
ChessGame::ChessGame() : board(std::make_unique<Board>()), scoreboard(std::make_unique<SimpleScoreBoard>()){
    textObserver = std::move(std::make_unique<TextObserver>(board.get()));
    graphicalObserver = std::move(std::make_unique<GraphicalObserver>(board.get()));
}

std::unique_ptr<Strategy> ChessGame::createStrategy(int level){
    if(level == 1){
        return std::make_unique<Level1>();
    }
    else if(level == 2){
        return std::make_unique<Level2>();
    }
    else if(level == 3){
        return std::make_unique<Level3>();
    }
    else if(level == 4){
        return std::make_unique<Level4>();
    }
    else{
        throw std::runtime_error("Specify computer level to be in [1-4]");
    }
}

void ChessGame::createPlayer(std::string player, Colour colour){
    try{
        if(player == "human"){
            auto newPlayer = std::make_unique<HumanPlayer>(colour, *board);
            players.push_back(std::move(newPlayer));
        }
        else if(player.substr(0, 8) == "computer"){
            int level = stoi(player.substr(9,1));
            strategies.push_back(std::move(createStrategy(level)));
            auto newPlayer = std::make_unique<ComputerPlayer>(colour, *board, *strategies.back());
            players.push_back(std::move(newPlayer));
        }
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
}
   
void ChessGame::addPlayers(std::string whitePlayer, std::string blackPlayer){
    createPlayer(whitePlayer, Colour::WHITE);
    createPlayer(blackPlayer, Colour::BLACK);
    turn = Colour::WHITE;
}

std::pair<int,int> getLocation(std::string loc){
    return {loc[1] - '1', loc[0] - 'a'};
}

void ChessGame::postMoveAction(Move playedMove){
    turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

    if (playedMove == Move()) {
        board->lastMove = board->getMoveHistory().empty() ? Move() : board->getMoveHistory().top();
    } else {
        board->lastMove = playedMove;
    }
    
    board->updateGameState(turn);
    GameState curState = board->getGameState();
    if(curState == GameState::BLACK_WINS || curState == GameState::WHITE_WINS || curState == GameState::DRAW){
        displayBoard();
        scoreboard->updateScores(ColourUtils::getWinner(curState));
        board->reset();
        std::cout<<"Game over!\n";
        return;
    }
    else if(curState == GameState::BLACK_IN_CHECK){
        std::cout << "Black in check" << std::endl;
    }
    else if(curState == GameState::WHITE_IN_CHECK){
        std::cout << "White in check" << std::endl;
    }
    displayBoard();
}

void ChessGame::displayBoard(){
    board->render();
}

// Method to move a piece from loc1 to loc2
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

    // Handle en passante
    Piece& piece = board->getPieceAt(newMove.oldPos.first, newMove.oldPos.second);
    int nr = newMove.newPos.first, nc = newMove.newPos.second;
    int r = newMove.oldPos.first, c = newMove.oldPos.second;
    int direction = turn == Colour::WHITE ? 1 : -1;
    if (dynamic_cast<const Pawn*>(&piece) != nullptr && board->isEmptyPosition(nr, nc) &&
        nr == r + direction && (nc == c + 1 || nc == c - 1)) {
        newMove.addPawnPromotion('e');
    }

    // Handle castling
    if (dynamic_cast<const King*>(&piece) != nullptr) {
        const King* king = dynamic_cast<const King*>(&piece);
        if (newMove.oldPos == king->getInitialPosition() && nr == r && (nc == c + 2 || nc == c - 2)) {
            newMove.addPawnPromotion('c');
        }
    }

    try{
        Move playedMove;
        if(turn == Colour::WHITE){
            playedMove = players[0]->playTurn(newMove);
        } else {
            playedMove = players[1]->playTurn(newMove);
        }
        postMoveAction(playedMove);
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
}

void ChessGame::movePiece(){
    try{
        Move playedMove;
        if(turn == Colour::WHITE){
            std::cout<<"white's move\n";
            playedMove = players[0]->playTurn();
        } else {
            std::cout<<"black's move\n";
            playedMove = players[1]->playTurn();
        }
        postMoveAction(playedMove);
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
}

// Method to accept resignation
void ChessGame::acceptResignation() {
    Colour winner = turn == Colour::BLACK ? Colour::WHITE : Colour::BLACK;
    scoreboard->updateScores(winner);
    board->reset();
    std::cout<<"Game over!\n";
}

// Method to set the turn
void ChessGame::setTurn(std::string colour) {
    turn = (colour == "white") ? Colour::WHITE : Colour::BLACK;
}

// Method to add a piece to the board
bool ChessGame::addPiece(std::string key, std::string loc) {
    if (!board->isEmptyPosition(getLocation(loc).first, getLocation(loc).second)) {
        return false;
    }
    
    std::unique_ptr<Piece> piece = std::move(PieceFactory::createPiece(key[0], *board));
    if (piece) {
        (*board).addPiece(std::move(piece), getLocation(loc));
    }
    return true;
}

// Method to remove a piece from the board
bool ChessGame::removePiece(std::string loc) {
    if (board->isEmptyPosition(getLocation(loc).first, getLocation(loc).second)) {
        return false;
    }

    board->removePiece(getLocation(loc));   
    return true;
}

// Method to check if the board configuration is valid
bool ChessGame::isBoardConfigValid() {
    return board->isValidConfig();
}

//Undo move
void ChessGame::undo() {
    try {
        board->undo();
    } catch (std::runtime_error e) {
        std::cerr << "An unknown error occurred. Forgive us!" << std::endl;
    }

    postMoveAction();
}
