#include "TextObserver.h"
#include "../Boards/Board.h"

//Concrete Observer Implementation

//Ctor: Initializes fields and sets studio object (non-owning)
TextObserver::TextObserver(Board* board, int width, int height)
    : width{width}, height{height}, board{board}{

    //Adds the observer to the subject
    board->attach(this);
}

//Overriden notify method 
void TextObserver::notify(){
    for(int i = height - 1; i >= 0; i--) {
         std::cout << i + 1 << " ";
        for (int j = 0; j < width; j++) {
            std::cout << board->getState(i, j);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "  ";
    
    for (char c = 'a'; c < 'a' + width; c++) {
        std::cout << c;
    }

    std::cout << std::endl;
}

//Dtor: Observer is removed from the subject
TextObserver::~TextObserver(){
    board->detach(this);
}
