#include "Level3.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"
#include <unordered_map>

Level3::Level3() {}

Move Level3::getStrategyImpl(Board& board, Colour colour) {
    int damage = 0;
    Piece* piece = nullptr;
    //Layer 1 - Avoid capture (minimize damage)
    for(auto it = board.begin(); it != board.end(); ++it){
        auto square = (*it);
        if(square.isEmpty() || square.piece->getColour() != colour) continue;
        auto curLoc = board.getPositionOfPiece(*square.piece);
        
        //Check for enemy moves
        for(auto it2 = board.begin(); it2 != board.end(); ++it2){
            auto enemySquare = (*it2);
            if(enemySquare.isEmpty() || enemySquare.piece->getColour() == colour) continue;
            auto enemyMoves = enemySquare.piece->getPossibleMoves();
            
            if(Move& emove: enemyMoves){
                if(emove.newPos.first == curLoc.first && emove.newPos.second == curLoc.second){
                    if(square.piece->getPoints() > damage){
                        damage = square.piece->getPoints();
                        piece = square.piece;
                    }
                }
            }
        }
        
    }

    //Layer 2 - Don't go somewhere where you would be captured
    std::vector<Move> possibleMoves;
    for(auto it = board.begin(); it != board.end(); ++it){
        auto square = (*it);
        if(square.isEmpty() || square.piece->getColour() != colour) continue;
        auto moves = square.piece->getPossibleMoves();
        
        for(auto& move: moves){
            
            //Simulate the move
            board.movePiece(move);

            bool canCapture = false;
            
            //Check for enemy moves
            for(auto it2 = board.begin(); it2 != board.end(); ++it2){
                auto enemySquare = (*it2);
                if(enemySquare.isEmpty() || enemySquare.piece->getColour() == colour) continue;
                auto enemyMoves = enemySquare.piece->getPossibleMoves();
                if(Move& emove: enemyMoves){
                    if(emove.newPos.first == move.newPos.first && emove.newPos.second == move.newPos.second){
                        canCapture = true;
                        break;
                    }
                }
            }

            //Revert the move
            board.movePiece(Move(move.newPos, move.oldPos));
            
            if(canCapture) continue;
            possibleMoves.push_back(move);
        }
    }
}
