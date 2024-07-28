#ifndef SQUARE_H
#define SQUARE_H
#include <memory>

class Piece;

class Square{
public:
    Piece * piece;
    Square(Piece* piece = nullptr);
    bool isEmpty() const;
    virtual ~Square() = default;
};

#endif
