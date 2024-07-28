#include "Level3.h"
#include "Level2.h"
#include "Board.h"
#include "Piece.h"
#include "Colour.h"
#include "Move.h"
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

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

    if(piecesWithThreat.size() == 0) return Level2::getStrategyImpl(board, colour);
    
    auto comparePieces = [](Piece* a, Piece* b) {
        if(!a || !b) throw std::runtime_error("Internal error - piece ptr is null");
        return a->getPoints() > b->getPoints(); 
    };
    std::sort(piecesWithThreat.begin(), piecesWithThreat.end(), comparePieces);

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
                for(auto& emove: enemyMoves){
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
