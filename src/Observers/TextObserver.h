#include "Observer.h"
#include <iostream>

class Board;
//Concrete Observer Declaration
class TextObserver: public Observer{
private:
    Board* board; //Non-owning ptr
    std::ostream &out = std::cout; //ostream object to print to console
    int width, height;
public:
    TextObserver(Board*, int width = 8, int height = 8);
    void notify() override;
    ~TextObserver();
};
