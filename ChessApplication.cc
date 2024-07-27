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
            std::cout << curLine << "\n";

            if(tokens.size() == 4){
                loc1 = tokens[1];
                loc2 = tokens[2];
                pawnPromotion = tokens[3][0];
                chessGame.movePiece(loc1, loc2, pawnPromotion);
            }

            // Extract loc1, loc2 from the line if available
            else if (tokens.size() == 3) {
                loc1 = tokens[1];
                loc2 = tokens[2];
                std::cout<<"moving piece from "<<loc1<<" to "<<loc2<<std::endl;
                chessGame.movePiece(loc1, loc2);
            } 
            
            else if (tokens.size() == 0){
                std::cout<<"moving piece"<<std::endl;
                chessGame.movePiece();
            }
        }

        else if(command == "setup"){
            std::string setupCmd;
            while(std::cin>>setupCmd){
                if(setupCmd == "+"){
                    std::string piece, loc;
                    std::cin>>piece>>loc;
                    std::cout << "added piece\n";
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