#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <utility>
#include "Piece.h"
#include "Square.h"
#include "GameState.h"

class Board {
private:
    std::vector<std::vector<std::unique_ptr<Square>>> grid;
    bool isCheckMate(Colour) const;
    bool isStaleMate(Colour) const;
    bool isKingInCheck(Colour) const;
    std::pair<int,int> kingLocation(Colour colour) const;
    std::vector<std::unique_ptr<Piece>> currentPieces; 
    GameState gameState;

public:
    Board(int rowSize = 8, int colSize = 8);
    void addPiece(std::unique_ptr<Piece>, std::pair<int,int>);
    void removePiece(std::pair<int, int>);
    void movePiece(const Move&);

    std::pair<int, int> getPositionOfPiece(const Piece&) const;
    Piece& getPieceAt(int, int) const;
    
    GameState getGameState() const;
    void updateGameState(Colour);
    bool isValidPosition(int, int) const;
    bool isEmptyPosition(int, int) const;
    bool isValidConfig();
    void reset();
    void render() const;
    char getState(int, int) const;
    
    bool isGameOver(Colour);
    Colour getWinner() const;
    
    template<typename T> class MyIterator{
        int row, col;
        std::vector<std::vector<std::unique_ptr<Square>>>& grid;
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
