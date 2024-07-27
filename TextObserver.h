#include "Observer.h"
#include <iostream>

class Board;
//Concrete Observer Declaration
class TextObserver: public Observer{
private:
    Board* board; //Non-owning ptr
    std::ostream &out = std::cout; //ostream object to print to console
    int top, bottom, left, right;
public:
    TextObserver(int, int, int, int, Board*);
    void notify() override;
    ~TextObserver();
};
