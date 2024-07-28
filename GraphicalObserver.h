#include "Observer.h"
#include "Window.h"

class Board;

//Concrete Observer Declaration
class GraphicalObserver: public Observer{   
private:
    Board* board; //Non-owning ptr to the concrete subject
    Xwindow window;
    int width, height;
public:
    GraphicalObserver(Board*, int width = 8, int height = 8);
    void notify() override;
    ~GraphicalObserver();
};
