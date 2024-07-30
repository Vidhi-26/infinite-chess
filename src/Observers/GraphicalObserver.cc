#include "GraphicalObserver.h"
#include "../Boards/Board.h"

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
    int row = 0;
    
    for (int i = height - 1; i >= 0; i--) {
        int col = 0;
        for (int j = 0; j < width; j++) {
            char currentState = board->getState(i, j);
            if (currentState != previousState[i][j]) {
                renderCell(row, col, currentState);
                previousState[i][j] = currentState;
            }
            col++;
        }
       
        row++;
    }

    if(board->movesToDisplay.size() > 0){
        for(int i = 0; i < board->movesToDisplay.size(); i++){
            auto newLoc = board->movesToDisplay[i].newPos;
            std::cout<<newLoc.first<<" "<<newLoc.second<<"\n";
            highlightCell(height - newLoc.first - 1, newLoc.second);
            previousState[newLoc.first][newLoc.second] = '.';
        }
        board->movesToDisplay.clear();
        board->movesToDisplay.resize(0);
    }
    

}

void GraphicalObserver::highlightCell(int row, int col) {
    // Define the highlight color, e.g., yellow
    int highlightColor = window.Yellow;

    // Fill the cell with the highlight color
    window.fillRectangle(100 * col, 100 * row, 100, 100, highlightColor);

    char currentState = board->getState(height - row - 1, col);
    // Determine the color for the piece text
    int textColor = (currentState >= 'a' && currentState <= 'z') ? window.Green : window.Red;

    // Draw the piece character if it's not an empty space
    if (currentState != ' ' && currentState != '_') {
        window.drawString(100 * col + 40, 100 * row + 60, std::string(1, currentState), textColor);
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
