#include "Square.h"

Square::Square(Piece* piece): piece{piece}{}

bool Square::isEmpty() const{
    if(piece) return false;
    return true;
}