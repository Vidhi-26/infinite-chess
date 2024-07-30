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
            std::string loc1, loc2;
            char pawnPromotion;

            // Read the entire line after the command
            std::string curLine;
            std::getline(std::cin, curLine);
            std::istringstream iss(curLine);
            
            std::vector<std::string> tokens;
            std::string token;
            while (std::getline(iss, token, ' ')) {
                tokens.push_back(token);
            }

            // Extract loc1, loc2, pawnPromotion from the line if available
            if(tokens.size() == 4){
                loc1 = tokens[1];
                loc2 = tokens[2];
                if (tokens[3].length() != 1) {
                    std::cout << "Invalid input. Cannot promote to " << tokens[3] << std::endl;
                    continue;   
                }
                pawnPromotion = tokens[3][0];

                chessGame.movePiece(loc1, loc2, pawnPromotion);
            }

            // Extract loc1, loc2 from the line if available
            else if (tokens.size() == 3) {
                loc1 = tokens[1];
                loc2 = tokens[2];
                chessGame.movePiece(loc1, loc2);
            } 
            
            else if (tokens.size() ==0){
                chessGame.movePiece();
            }
        }

        else if(command == "setup"){
            if(chessGame.isGameRunning()){
                std::cout<<"Game is still running! Can't enter setup mode"<<std::endl;
            }
            else{
                std::string setupCmd;
                while(std::cin>>setupCmd){
                    if(setupCmd == "+"){
                        std::string piece, loc;
                        std::cin>>piece>>loc;
                        if (!chessGame.addPiece(piece,loc)) {
                            std::cout << "Add failed. Another already exists here!" << std::endl;
                        }
                        chessGame.displayBoard();
                    }
                    else if(setupCmd == "-"){
                        std::string piece, loc;
                        std::cin>>piece>>loc;
                        if (!chessGame.removePiece(loc)) {
                            std::cout << "Remove failed. No piece exists here!" << std::endl;
                        }
                        chessGame.displayBoard();
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
            
        }
        else{
            std::cout<<"Wrong command. Try again!"<<std::endl;
        }
    }
    
    return 0;
}
