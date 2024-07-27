#include "Board.h"
#include "King.h"
#include "Move.h"
#include "Pawn.h"
#include "GameState.h"
#include <stdexcept>
#include <unordered_map>

Board::Board(int rowSize, int colSize) : grid(rowSize, std::vector<std::unique_ptr<Square>>(colSize)){}

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

bool Board::isValidConfig(){
    auto whiteKingLoc = kingLocation(Colour::BLACK);
    auto blackKingLoc = kingLocation(Colour::WHITE);
    if(whiteKingLoc.first == -1 || whiteKingLoc.second == -1 || blackKingLoc.first == -1 || whiteKingLoc.first == -1) return false;
    if(isKingInCheck(Colour::BLACK) || isKingInCheck(Colour::WHITE)) return false;
    
    for(int i = 0; i < grid[0].size(); i++){
        if(dynamic_cast<Pawn*>(grid[0][i]->piece)) return false;
    }

    for(int i = 0; i < grid[grid.size() - 1].size(); i++){
        if(dynamic_cast<Pawn*>(grid[grid.size() - 1][i]->piece)) return false;
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
    grid[loc.first][loc.second] = nullptr;
}

void Board::reset(){
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); i++){
            removePiece({i,j});
        }
    }
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

bool Board::isCheckMate(Colour colour) const{
    auto kingLoc = kingLocation(colour);
    Piece& piece = getPieceAt(kingLoc.first, kingLoc.second);
    auto kingMoves = piece.getPossibleMoves();
    std::unordered_map<std::pair<int,int>, bool, pair_hash> moveNotPossible;
    
    //Start by assuming all king moves are possible
    for(int i = 0; i < kingMoves.size(); i++){
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

bool Board::isGameOver(Colour turn) {
   
}

//Returns king location on the board given the colour. 
//Special cases: If king does not exist, or exists multiple times, returns {-1,-1}
std::pair<int,int> Board::kingLocation(Colour colour) const{
    std::pair<int,int> kingLoc = {-1,-1};

    //Iterate through the chess board
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(!grid[i][j]->isEmpty() && grid[i][j]->piece->getColour() == colour && dynamic_cast<King*>(grid[i][j]->piece)){
                
                //Found a 2nd King
                if(kingLoc.first != -1 && kingLoc.second != -1) { 
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
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); i++){
            if(!grid[i][j]->isEmpty() && grid[i][j]->piece->getColour() != colour){
                auto moves = grid[i][j]->piece->getPossibleMoves();
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
        
        bool blackCheckMate= isCheckMate(Colour::BLACK);
        if(blackCheckMate){
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
