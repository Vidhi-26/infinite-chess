#include "Board.h"
#include "../Pieces/King.h"
#include "../Moves/Move.h"
#include "../Pieces/Pawn.h"
#include "../GameState.h"
#include <stdexcept>
#include <unordered_map>
#include <iostream>

Board::Board(int rowSize, int colSize) : grid(rowSize) {
    for (auto& row : grid) {
        row.reserve(colSize);
        for (int i = 0; i < colSize; ++i) {
            row.push_back(std::make_unique<Square>());
        }
    }
}

std::pair<int, int> Board::getPositionOfPiece(const Piece& piece) const {
    for (size_t r = 0; r < grid.size(); r++) {
        for (size_t c = 0; c < grid[r].size(); c++) {
            if (!grid[r][c]->isEmpty() && grid[r][c]->piece == &piece) {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

Piece& Board::getPieceAt(int r, int c) const {
    if (grid[r][c]->isEmpty()) {
        throw std::runtime_error("No piece at the specified location");
    }
    return *grid[r][c]->piece;
}

bool Board::isValidPosition(int r, int c) const {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[r].size();
}

bool Board::isEmptyPosition(int r, int c) const {
    return grid[r][c]->isEmpty();
}

bool Board::isValidConfig() {
    auto whiteKingLoc = kingLocation(Colour::BLACK);
    auto blackKingLoc = kingLocation(Colour::WHITE);
    if(whiteKingLoc.first == -1 || whiteKingLoc.second == -1 || blackKingLoc.first == -1 || whiteKingLoc.first == -1) return false;
    if(isKingInCheck(Colour::BLACK) || isKingInCheck(Colour::WHITE)) return false;
    
    for(size_t i = 0; i < grid[0].size(); i++){
        if(!grid[0][i]->isEmpty() && dynamic_cast<Pawn*>(grid[0][i]->piece)) return false;
    }

    for(size_t i = 0; i < grid[grid.size() - 1].size(); i++){
        if(!grid[0][i]->isEmpty() && dynamic_cast<Pawn*>(grid[grid.size() - 1][i]->piece)) return false;
    }
    return true;
}

void Board::addPiece(std::unique_ptr<Piece> piece, std::pair<int,int> loc){
    //TODO: check if piece already exists in pieces vector
    grid[loc.first][loc.second]->piece = piece.get();
    currentPieces.push_back(std::move(piece));
}

void Board::removePiece(std::pair<int, int> loc){
    Piece& piece = getPieceAt(loc.first, loc.second);
    for(auto it = currentPieces.begin(); it != currentPieces.end(); ++it){
        if((*it).get() == &piece){
            currentPieces.erase(it);
            break;
        }
    }
    grid[loc.first][loc.second]->piece = nullptr;
}

void Board::reset(){
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            if(!grid[i][j]->isEmpty()){
                grid[i][j]->piece = nullptr;
            }
        }
    }
    while(currentPieces.size() > 0) currentPieces.pop_back();
}

bool Board::isStaleMate(Colour turn) const{
    //Iterate through all the squares on the board
    for(auto it = cbegin(); it != cend(); ++it){
        auto square = *it;

        //Check if current square has an enemy
        if(!square.isEmpty() && square.piece->getColour() == turn){
            auto curMoves = square.piece->getPossibleMoves();
            if(curMoves.size() > 0) return false;
        }
    }
    return true;
}

// Define a custom hash function for std::pair<int, int>
struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        // Use a combination of the hashes of the two integers
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

// Check for enemy moves to see if they can capture the piece
bool Board::isPositionUnderAttack(int r, int c, Colour colour) const {
    for(int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j]->isEmpty() || grid[i][j]->piece->getColour() == colour ||
                dynamic_cast<const King*>(grid[i][j]->piece)) continue;
            auto enemyMoves = grid[i][j]->piece->getPossibleMoves(true);           
            for(auto& emove: enemyMoves){
                if(emove.newPos.first == r && emove.newPos.second == c){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckMate(Colour colour) const{
    auto kingLoc = kingLocation(colour);
    Piece& piece = getPieceAt(kingLoc.first, kingLoc.second);
    auto kingMoves = piece.getPossibleMoves();
    std::unordered_map<std::pair<int,int>, bool, pair_hash> moveNotPossible;
    
    //Start by assuming all king moves are possible
    for(size_t i = 0; i < kingMoves.size(); i++){
        moveNotPossible[kingMoves[i].newPos] = false;
    }
    
    //Iterate through all the squares on the board
    for(auto it = cbegin(); it != cend(); ++it){
        auto square = *it;

        //Check if current square has an enemy
        if(!square.isEmpty() && square.piece->getColour() != colour){
            auto enemyMoves = square.piece->getPossibleMoves(true);
            
            //Iterate through the moves of the enemy and check if the move conflicts with possible king move
            for(auto move: enemyMoves){
                if(moveNotPossible.find(move.newPos) != moveNotPossible.end()) moveNotPossible[move.newPos] = true;
            }
            
        }
    }

    for(auto move: kingMoves){
        if(!moveNotPossible[move.newPos]) return false;
    }
    return true;
}


//Returns king location on the board given the colour. 
//Special cases: If king does not exist, or exists multiple times, returns {-1,-1}
std::pair<int,int> Board::kingLocation(Colour colour) const{
    std::pair<int,int> kingLoc = {-1,-1};

    //Iterate through the chess board
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            if(!grid[i][j]->isEmpty() && grid[i][j]->piece->getColour() == colour && dynamic_cast<const King*>(grid[i][j]->piece)){
                
                //Found a 2nd King
                if(kingLoc.first != -1 && kingLoc.second != -1) {
                    std::cout<<"Found 2nd king\n"; 
                    return {-1,-1};
                }
                else kingLoc = {i,j};
            }
        }
    }
    return kingLoc;
}

//Returns if a king is in check given the colour
bool Board::isKingInCheck(Colour colour) const{
    auto kingLoc = kingLocation(colour);
    if(kingLoc.first == -1 || kingLoc.second == -1) throw std::runtime_error("No king found");

    //Iterate through the chess board
    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[i].size(); j++){
            if(!grid[i][j]->isEmpty() && grid[i][j]->piece->getColour() != colour){
                auto moves = grid[i][j]->piece->getPossibleMoves(true);
                for(auto& move: moves){
                    if(move.newPos.first == kingLoc.first && move.newPos.second == kingLoc.second) return true;
                }
            }
        }
    }
    return false;
}

GameState Board::getGameState() const{
    return gameState;
}

void Board::updateGameState(Colour turn){
    bool blackKingCheck = isKingInCheck(Colour::BLACK);
    bool whiteKingCheck = isKingInCheck(Colour::WHITE);

    if(blackKingCheck && whiteKingCheck){
        throw std::runtime_error("Double check! Can't be possible");
    }
    if(blackKingCheck){
        bool blackCheckMate = isCheckMate(Colour::BLACK);
        if(blackCheckMate) {
            gameState = GameState::WHITE_WINS;
        }
        else gameState = GameState::BLACK_IN_CHECK;
    }
    else if(whiteKingCheck){
        bool whiteCheckMate = isCheckMate(Colour::WHITE);
        if(whiteCheckMate){
            gameState = GameState::BLACK_WINS;
        }
        else gameState = GameState::WHITE_IN_CHECK;
    }
    else if(isStaleMate(turn)) {
        gameState = GameState::DRAW;
    }
    else gameState = GameState::IN_PROGRESS;
}

// For tracking move history
std::stack<Move> Board::getMoveHistory() const {
    return moveHistory;
}

void Board::addToMoveHistory(Move move) {
    moveHistory.push(move);
}

// Move simulations
void Board::movePiece(const Move& move) {
    //std::cout<<"In move piece "<<grid[move.oldPos.first][move.oldPos.second]->piece->getCode()<<std::endl;
    grid[move.newPos.first][move.newPos.second]->piece = grid[move.oldPos.first][move.oldPos.second]->piece;
    grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;
}

Piece* Board::simulateMovePiece(const Move& move) {
    //std::cout<<"In simulate move piece "<<grid[move.oldPos.first][move.oldPos.second]->piece->getCode()<<std::endl;
    Piece* capturedPiece = grid[move.newPos.first][move.newPos.second]->piece;
    grid[move.newPos.first][move.newPos.second]->piece = grid[move.oldPos.first][move.oldPos.second]->piece;
    grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;
    return capturedPiece;
}

std::pair<Piece*, Piece*> Board::simulateMovePiece(const Move& move, std::unique_ptr<Piece> newPawnPromotionPiece) {
    //std::cout<<"In simulate move piece with pawn "<<grid[move.oldPos.first][move.oldPos.second]->piece->getCode()<<std::endl;
    Piece* capturedPiece = grid[move.newPos.first][move.newPos.second]->piece;
    Piece* originalPawnPiece = grid[move.oldPos.first][move.oldPos.second]->piece;
    grid[move.newPos.first][move.newPos.second]->piece = newPawnPromotionPiece.get();
    grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;

    simulatedPawnPromotions.push_back(std::move(newPawnPromotionPiece));

    return {capturedPiece, originalPawnPiece};
}

Piece* Board::simulateMovePiece(const Move& move, char specialReq) {
    if (specialReq == 'e') {
        Piece* capturedPawn = grid[move.oldPos.first][move.newPos.second]->piece;

        grid[move.newPos.first][move.newPos.second]->piece = grid[move.oldPos.first][move.oldPos.second]->piece;
        grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;
        grid[move.oldPos.first][move.newPos.second]->piece = nullptr;   // en-passante pawn

        return capturedPawn;
    } else if (specialReq == 'c') {                                     // castle case
        grid[move.newPos.first][move.newPos.second]->piece = grid[move.oldPos.first][move.oldPos.second]->piece;
        grid[move.oldPos.first][move.oldPos.second]->piece = nullptr;

        if (move.newPos.second > move.oldPos.second) {
            grid[move.newPos.first][move.newPos.second - 1]->piece = grid[move.newPos.first][move.newPos.second + 1]->piece;
            grid[move.newPos.first][move.newPos.second + 1]->piece = nullptr;
        } else {
            grid[move.newPos.first][move.newPos.second + 1]->piece = grid[move.newPos.first][move.newPos.second - 2]->piece;
            grid[move.newPos.first][move.newPos.second - 2]->piece = nullptr;
        }
    }
    return nullptr;
}

// Undo move simulations
void Board::undoSimulatedMove(const Move& move) {
    grid[move.oldPos.first][move.oldPos.second]->piece = grid[move.newPos.first][move.newPos.second]->piece;
    grid[move.newPos.first][move.newPos.second]->piece = nullptr;

    if (move.newPos.second > move.oldPos.second) {
        grid[move.newPos.first][move.newPos.second + 1]->piece = grid[move.newPos.first][move.newPos.second - 1]->piece;
        grid[move.newPos.first][move.newPos.second - 1]->piece = nullptr;
    } else {
        grid[move.newPos.first][move.newPos.second - 2]->piece = grid[move.newPos.first][move.newPos.second + 1]->piece;
        grid[move.newPos.first][move.newPos.second + 1]->piece = nullptr;
    }
}

void Board::undoSimulatedMove(const Move& move, Piece* capturedPiece) {
    //std::cout<<"In simulate undo piece "<<grid[move.oldPos.first][move.oldPos.second]->piece->getCode()<<std::endl;
    grid[move.oldPos.first][move.oldPos.second]->piece = grid[move.newPos.first][move.newPos.second]->piece;
    grid[move.newPos.first][move.newPos.second]->piece = capturedPiece;
}

void Board::undoSimulatedMove(const Move& move, Piece* capturedPiece, Piece* originalPawnPiece) {
    //std::cout<<"In simulate undo piece with pawn "<<grid[move.oldPos.first][move.oldPos.second]->piece->getCode()<<std::endl;
    for(auto it = simulatedPawnPromotions.begin(); it != simulatedPawnPromotions.end(); ++it){
        if((*it).get() == grid[move.oldPos.first][move.oldPos.second]->piece){
            simulatedPawnPromotions.erase(it);
            break;
        }
    }

    grid[move.oldPos.first][move.oldPos.second]->piece = originalPawnPiece;
    grid[move.newPos.first][move.newPos.second]->piece = capturedPiece;
}

void Board::undoSimulatedMove(const Move& move, Piece* capturedPawn, char specialReq) {
    if (specialReq == 'e') {
        grid[move.oldPos.first][move.oldPos.second]->piece = grid[move.newPos.first][move.newPos.second]->piece;
        grid[move.newPos.first][move.newPos.second]->piece = nullptr;
        grid[move.oldPos.first][move.newPos.second]->piece = capturedPawn;
    }
}

void Board::render() {
    this->notifyObservers();
}

char Board::getState(int row, int col) const{
    if(grid[row][col]->isEmpty()){
        if(row % 2 == 0 && col % 2 == 0) return '_';
        else if(row % 2 != 0 && col % 2 != 0) return '_';
        else return ' ';
    } 
    
    char code = grid[row][col]->piece->getCode();
    if(grid[row][col]->piece->getColour() == Colour::WHITE){
        return code - 32;
    }
    return code; 
}
