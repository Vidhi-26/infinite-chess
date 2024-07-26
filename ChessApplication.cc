#include <iostream>
#include "ChessGame.h"
#include <sstream>

int main(){
    ChessGame chessGame;
    std::string command;

    while (std::cin >> command) {
        if (command == "game" ) {
            std::string whitePlayer, blackPlayer;
            std::cin>>whitePlayer>>blackPlayer;
            chessGame.addPlayers(whitePlayer, blackPlayer);
        }
        else if(command == "resign"){
            chessGame.acceptResignation();
        }

        else if(command == "move"){
            std::string loc1, loc2, pawnPromotion;
            
            // Read the entire line after the command
            std::string curLine;
            std::getline(std::cin, curLine);
            std::istringstream iss(curLine);
            
            // Extract loc1, loc2, pawnPromotion from the line if available
            if(iss>> loc1 >> loc2 >> pawnPromotion){
                chessGame.movePiece(loc1, loc2, pawnPromotion);
            }

            // Extract loc1, loc2 from the line if available
            else if (iss >> loc1 >> loc2) {
                chessGame.movePiece(loc1, loc2);
            } 
            
            else {
                chessGame.movePiece();
            }
        }

        else if(command == "setup"){
            std::string setupCmd;
            while(std::cin>>setupCmd){
                if(setupCmd == "+"){
                    std::string piece, loc;
                    std::cin>>piece>>loc;
                    chessGame.addPiece(piece,loc);
                }
                else if(setupCmd == "-"){
                    std::string loc;
                    std::cin>>loc;
                    chessGame.removePiece(loc);
                }
                else if(setupCmd == "="){
                    std::string colour;
                    std::cin>>colour;
                    chessGame.setTurn(colour);
                }
                else if(setupCmd == "done"){
                    if(chessGame.isBoardConfigValid()) break;
                    else{
                        std::cout<<"Setup Failed!"<<std::endl;
                    }
                }
                else{
                    std::cout<<"Wrong setup command. Try again!"<<std::endl;
                }
            }
        }
        else{
            std::cout<<"Wrong command. Try again!"<<std::endl;
        }
    }
    
    return 0;
}