#include "Observer.h"
#include "Window.h"
#include <vector>

class Board;

//Concrete Observer Declaration
class GraphicalObserver: public Observer{   
private:
    Board* board; //Non-owning ptr to the concrete subject
    Xwindow window;
    int width, height;
    std::vector<std::vector<char>> previousState;  // Store the previous state
    void renderCell(int row, int col, char state);  // Render a single cell
    void highlightCell(int row, int col);
public:
    GraphicalObserver(Board*, int width = 8, int height = 8);
    void notify() override;
    ~GraphicalObserver();
};
