#include "ChessGame.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

int main(){
    ChessGame chessGame;
    std::string command;

    // Command interpreter
    while (std::cin >> command) {
        if (command == "game") {
            // Can start game only from setup state
            if(!chessGame.isBoardConfigValid() || chessGame.isInProgress() || chessGame.isGameStateInCheck()) {
                std::cout<<"Board must be in setup stage before playing :)"<<std::endl;
            } else {
                std::string whitePlayer, blackPlayer;
                std::cin>>whitePlayer>>blackPlayer;

                // Can only be one of the possible players
                std::unordered_set<std::string> possiblePlayers = {"human", "computer[1]", "computer[2]", "computer[3]", "computer[4]", "computer[5]"};
                if (whitePlayer.empty() || blackPlayer.empty() || possiblePlayers.find(whitePlayer) == possiblePlayers.end() || possiblePlayers.find(blackPlayer) == possiblePlayers.end()) {
                    std::cout << "Invalid player types" << std::endl;
                } else {
                    chessGame.addPlayers(whitePlayer, blackPlayer);   
                    chessGame.setInProgress();
                }
            }
        } else if(command == "resign") {
            // Can resign only if game is in progress state
            if(!(chessGame.isInProgress() || chessGame.isGameStateInCheck())){
                std::cout<<"Invalid command! Game is not running"<<std::endl;
            } else {
                chessGame.acceptResignation();
            }
        } else if (command == "undo") {
            // Can undo only if game is in progress state
            if(!(chessGame.isInProgress() || chessGame.isGameStateInCheck())){
                std::cout<<"Invalid command! Game is not running"<<std::endl;
            } else {
                chessGame.undo();
            }
        } else if(command == "move") {
            // Can move only if game is in progress state
            if(!(chessGame.isInProgress() || chessGame.isGameStateInCheck())){
                std::cout<<"Invalid command! Game is not running"<<std::endl;
            } else {
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
                if (tokens.size() == 4) {
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
                else if (tokens.size() == 0) {
                    chessGame.movePiece();
                } else {
                    std::cout << "Invalid move command. Try again!" << std::endl;
                }
            }
        }

        else if(command == "setup"){
            chessGame.displayBoard();
            // Can only enter setup if game is not running
            if(chessGame.isGameRunning()){
                std::cout<<"Game is still running! Can't enter setup mode"<<std::endl;
            }
            else{
                std::string setupCmd;
                while(std::cin>>setupCmd){
                    if(setupCmd == "+"){    
                        std::string piece, loc;         // Add piece to board
                        std::cin>>piece>>loc;

                        // only one of following pieces
                        std::unordered_set<char> validPieces = {'K', 'Q', 'N', 'B', 'R', 'P'};
                        if (piece.length() != 1 || validPieces.find(std::toupper(piece[0])) == validPieces.end() || !chessGame.isValidLocation(loc)) {
                            std::cout << "Invalid piece or location. Try again." << std::endl;
                            continue;
                        }
                        if (!chessGame.addPiece(piece,loc)) {
                            std::cout << "Add failed. Another already exists here!" << std::endl;
                        }
                        chessGame.displayBoard();
                    } else if(setupCmd == "-"){         // Remove piece from board
                        std::string loc;
                        std::cin>>loc;
                        if (!chessGame.isValidLocation(loc)) {
                            std::cout << "Invalid location. Try again." << std::endl;
                            continue;
                        }
                        if (!chessGame.removePiece(loc)) {
                            std::cout << "Remove failed. No piece exists here!" << std::endl;
                        }
                        chessGame.displayBoard();
                    } else if(setupCmd == "="){         // Switch player color
                        std::string colour;
                        std::cin>>colour;
                        chessGame.setTurn(colour);
                    } else if(setupCmd == "done"){      // Exit setup only if board config is valid
                        if(chessGame.isBoardConfigValid()) {
                            break;
                        } else {
                            std::cout<<"Setup Failed!"<<std::endl;
                        }
                    } else{
                        std::cout<<"Wrong setup command. Try again!"<<std::endl;
                    }
                }
            }
        } else if (command == "help") {
            // Can only ask for help if game is not in progress
            if(!(chessGame.isInProgress() || chessGame.isGameStateInCheck())){
                std::cout<<"Invalid command! Game is not running"<<std::endl;
            } else {
                // Show possible moves from loc
                std::string loc;
                std::cin>>loc;
                chessGame.help(loc);
            }
        } else if(command == "quit"){
            break;
        } else {
            std::cout<<"Wrong command. Try again!"<<std::endl;
        }
    }
    
    return 0;
}
