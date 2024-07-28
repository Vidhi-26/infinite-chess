#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <utility>
#include "Piece.h"
#include "Square.h"
#include "GameState.h"
#include "Subject.h"

class Board: public Subject {
private:
    std::vector<std::vector<std::unique_ptr<Square>>> grid;
    std::vector<std::unique_ptr<Piece>> currentPieces;
    GameState gameState; 

    // Helper methods to detect checkmate and stalemate situations
    bool isCheckMate(Colour) const;
    bool isStaleMate(Colour) const;
    std::pair<int,int> kingLocation(Colour colour) const;

public:
    // Board ctor and methods to add, remove, move pieces on board
    Board(int rowSize = 8, int colSize = 8);
    void addPiece(std::unique_ptr<Piece>, std::pair<int,int>);
    void removePiece(std::pair<int, int>);
    void movePiece(const Move&);

    // Move simulations
    Piece* simulateMovePiece(const Move&);
    std::pair<Piece*, Piece*> simulateMovePiece(const Move&, Piece*);
    void undoSimulatedMove(const Move&, Piece*);
    void undoSimulatedMove(const Move&, Piece*, Piece*);

    // Getters for board pieces
    std::pair<int, int> getPositionOfPiece(const Piece&) const;
    Piece& getPieceAt(int, int) const;

    // Setter and getter for game state
    GameState getGameState() const;
    void updateGameState(Colour);

    // Checks if a square is at a valid position and configuration of all pieces is valid
    bool isValidPosition(int, int) const;
    bool isEmptyPosition(int, int) const;
    bool isValidConfig();

    // Helps in displaying board
    void reset();
    void render();
    char getState(int, int) const;
    
    // Methods to check when game might be over
    bool isKingInCheck(Colour) const;
    
    // Iterates grid
    template<typename T> class MyIterator{
        int row, col;
        const std::vector<std::vector<std::unique_ptr<Square>>>& grid;
        MyIterator<T>(int r, int c, const std::vector<std::vector<std::unique_ptr<Square>>>& grid): row{r}, col{c}, grid{grid}{}
    public:
        bool operator!= (const MyIterator<T>& other){
            return other.row != row || other.col != col;
        }

        MyIterator<T>& operator++(){
            col++;
            if(col == grid[row].size()){
                col = 0;
                row++;
            }
            return *this;
        }

        T operator*(){
            return *grid[row][col];
        }

        friend class Board;
    };

    using Iterator = MyIterator<Square&>;
    using ConstIterator = MyIterator<const Square&>;

    Iterator begin(){ return MyIterator<Square&>{0,0, grid}; }
    Iterator end() {return MyIterator<Square&>{grid.size(), 0, grid};}

    ConstIterator cbegin() const{ return MyIterator<const Square&>{0,0, grid}; }
    ConstIterator cend() const {return MyIterator<const Square&>{grid.size(), 0, grid};}  
};

#endif
