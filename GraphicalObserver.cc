#include "GraphicalObserver.h"
#include "Board.h"

// Concrete Observer Implementation

// Ctor: Initialize window to 10c and 10r
// Set the studio field (subject)
GraphicalObserver::GraphicalObserver(Board* board, int width, int height)
    : width{width}, height{height}, board{board}, window{100 * width, 100 * height} {
    
    // Attach the observer to the subject
    board->attach(this); 
}

// Overriden notify method
void GraphicalObserver::notify() {
    int row = 0;
    int col = 0;

    // Iterate through board (for the requested bounds) and render each cell
    for (int i = height - 1; i >= 0; i--) {
        col = 0;
        for (int j = 0; j < width; j++) {

            // Get the state of each cell via the subject
            char c = board->getState(i, j);
            int color;

            // Determine the color for the background
            if ((i + j) % 2 == 0) {
                color = window.White;
            } else {
                color = window.Black;
            }

            // Make each cell 100x100
            window.fillRectangle(100 * col, 100 * row, 100, 100, color);

            // Determine the color for the piece text
            int textColor = (c >= 'a' && c <= 'z') ? window.Green : window.Red;

            // Draw the piece character if it's not an empty space
            if (c != ' ' &&  c != '_') {
                window.drawString(100 * col + 40, 100 * row + 60, std::string(1, c), textColor);
            }

            col++;
        }
        row++;
    }
}

// Dtor: Observer is removed from the subject
GraphicalObserver::~GraphicalObserver() {
    board->detach(this);
}
