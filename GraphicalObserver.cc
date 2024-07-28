#include "GraphicalObserver.h"
#include "Board.h"

// Concrete Observer Implementation

// Ctor: Initialize window to 10c and 10r
// Set the studio field (subject)
GraphicalObserver::GraphicalObserver(Board* board, int width, int height)
    : width{width}, height{height}, board{board}, window{100 * width, 100 * height} {
    
    // Attach the observer to the subject
    board->attach(this); 

    this->previousState.resize(height, std::vector<char>(width, '*'));
}

// Overriden notify method
void GraphicalObserver::notify() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char currentState = board->getState(i, j);
            if (currentState != previousState[i][j]) {
                renderCell(i, j, currentState);
                previousState[i][j] = currentState;
            }
        }
    }
}

void GraphicalObserver::renderCell(int row, int col, char state) {
    int color;
    // Determine the color for the background
    if ((row + col) % 2 == 0) {
        color = window.White;
    } else {
        color = window.Black;
    }

    // Make each cell 100x100
    window.fillRectangle(100 * col, 100 * row, 100, 100, color);

    // Determine the color for the piece text
    int textColor = (state >= 'a' && state <= 'z') ? window.Green : window.Red;

    // Draw the piece character if it's not an empty space
    if (state != ' ' && state != '_') {
        window.drawString(100 * col + 40, 100 * row + 60, std::string(1, state), textColor);
    }
}


// Dtor: Observer is removed from the subject
GraphicalObserver::~GraphicalObserver() {
    board->detach(this);
}
