#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <utility>
#include "Piece.h"

class Board {
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> pieces;

public:
    void addPiece(std::unique_ptr<Piece>);
    void removePiece(std::pair<int, int>);

    std::pair<int, int> getPositionOfPiece(const Piece&) const;
    Piece& getPieceAt(int, int) const;
    
    bool isValidPosition(int, int) const;
    bool isEmptyPosition(int, int) const;
    bool isValidConfig();
    void reset();
    void render() const;
    char getState(int, int) const;
    
    bool isGameOver() const;
    Colour getWinner() const;
   

    template<typename T> class MyIterator{
        int row, col;
        std::vector<std::vector<std::unique_ptr<Piece>>>& pieces;
        MyIterator<T>(int r, int c, const std::vector<std::vector<std::unique_ptr<Piece>>>& pieces): row{r}, col{c}, pieces{pieces}{}
    public:
        bool operator!= (const MyIterator<T>& other){
            return other.row != row || other.col != col;
        }
        MyIterator<T>& operator++(){
            col++;
            if(col == pieces[row].size()){
                col = 0;
                row++;
            }
            return *this;
        }
        T operator*(){
            return *pieces[row][col];
        }

        friend class Board;
    };

    using Iterator = MyIterator<Piece&>;
    using ConstIterator = MyIterator<const Piece&>;

    Iterator begin(){ return MyIterator<Piece&>{0,0, pieces}; }
    Iterator end() {return MyIterator<Piece&>{pieces.size(), 0, pieces};}

    ConstIterator cbegin() const{ return MyIterator<const Piece&>{0,0, pieces}; }
    ConstIterator cend() const {return MyIterator<const Piece&>{pieces.size(), 0, pieces};}
    
};

#endif
