#include "Level3.h"
#include "Level2.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"
#include "StrategyUtils.h"
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <iostream>

Level3::Level3() {}

Move Level3::getStrategyImpl(Board& board, Colour colour) {
    std::vector<Piece*> piecesWithThreat;
    
    //Layer 1 - Get all the pieces which are under a threat
    for(auto it = board.begin(); it != board.end(); ++it){
        auto square = (*it);
        if(square.isEmpty() || square.piece->getColour() != colour) continue;
        auto curLoc = board.getPositionOfPiece(*square.piece);
        
        bool threat = false;

        //For each piece, check for enemy moves to see if they can capture the piece
        for(auto it2 = board.begin(); it2 != board.end(); ++it2){
            auto enemySquare = (*it2);
            if(enemySquare.isEmpty() || enemySquare.piece->getColour() == colour) continue;
            auto enemyMoves = enemySquare.piece->getPossibleMoves();
            
            for(auto& emove: enemyMoves){
                if(emove.newPos.first == curLoc.first && emove.newPos.second == curLoc.second){
                    piecesWithThreat.push_back(square.piece);
                    threat = true;
                    break;
                }
            }
            if(threat) break;
        }
    }

    //If no pieces are under a threat, then add all the pieces
    if(piecesWithThreat.size() == 0) {
        // for(auto it = board.begin(); it != board.end(); ++it){
        //     auto square = (*it);
        //     if(!square.isEmpty() && square.piece->getColour() == colour) {
        //         piecesWithThreat.push_back(square.piece);
        //     }
        // }
        std::vector<Move> possibleMoves;
        possibleMoves.push_back(Level2::getStrategyImpl(board, colour));
        possibleMoves.push_back(Level1::getStrategyImpl(board, colour));
        return StrategyUtils::getRandomMove(possibleMoves);
    }
    
    //Layer 2: For all the pieces that have a threat, try to move the piece that is worth the most
    auto comparePieces = [](Piece* a, Piece* b) {
        if(!a || !b) throw std::runtime_error("Internal error - piece ptr is null");
        return a->getPoints() > b->getPoints(); 
    };
    std::sort(piecesWithThreat.begin(), piecesWithThreat.end(), comparePieces);

    for(auto it = piecesWithThreat.begin(); it != piecesWithThreat.end(); ++it){
      
        auto moves = (*it)->getPossibleMoves();
        
        std::vector<Move> safeMoves;
        for(auto& move: moves){
            
            //Simulate the move
            board.movePiece(move);

            bool canCapture = false;
            
            //Check for enemy moves
            for(auto it2 = board.begin(); it2 != board.end(); ++it2){
                auto enemySquare = (*it2);
                if(enemySquare.isEmpty() || enemySquare.piece->getColour() == colour) continue;
                auto enemyMoves = enemySquare.piece->getPossibleMoves();
                for(auto& emove: enemyMoves){
                    if(emove.newPos.first == move.newPos.first && emove.newPos.second == move.newPos.second){
                        canCapture = true;
                        break;
                    }
                }
                if(canCapture) break;
            }

            //Revert the move
            board.movePiece(Move(move.newPos, move.oldPos));
            
            if(canCapture) continue;
            safeMoves.push_back(move);
        }
        if(safeMoves.size() > 0){
            Move selectedMove = StrategyUtils::getRandomMove(safeMoves);
            std::cout<<"Level 3 move: "<<selectedMove.oldPos.first<<" "<<selectedMove.oldPos.second<<" "<<selectedMove.newPos.first<<" "<<selectedMove.newPos.second<<std::endl;
            return selectedMove;
        }
    }
    return Level2::getStrategyImpl(board, colour);
}
