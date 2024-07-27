#include "TextObserver.h"
#include "Board.h"

//Concrete Observer Implementation

//Ctor: Initializes fields and sets studio object (non-owning)
TextObserver::TextObserver(int top, int bottom, int left, int right, Board* board)
    : top{top}, bottom{bottom}, left{left}, right{right}, board{board}{

    //Adds the observer to the subject
    board->attach(this);
}

//Overriden notify method 
void TextObserver::notify(){

    //Displays text-based render based on the state of each cell
    //Iterates from left --> right and top --> bottom
    out << '+';
    for (int j = left; j <= right; ++j) out << '-';
    out << '+' << std::endl;
    for (int i = top; i <= bottom; ++i) {
        out << '|';
        for (int j = left; j <= right; ++j) {
        out << board->getState(i, j); //Gets the character that should be displayed
        }
        out << '|' << std::endl;
    }
    out << '+';
    for (int j = left; j <= right; ++j) out << '-';
    out << '+' << std::endl;
}

//Dtor: Observer is removed from the subject
TextObserver::~TextObserver(){
    board->detach(this);
}
