#include "ColourUtils.h"

std::string ColourUtils::toString(Colour colour) {
    switch (colour) {
        case Colour::WHITE: return "White";
        case Colour::BLACK: return "Black";
        // Add other colour cases later if needed
        default: return "Unknown Colour";
    }
}

Colour ColourUtils::getWinner(GameState gs) {
    switch (gs) {
        case GameState::WHITE_WINS: return Colour::WHITE;
        case GameState::BLACK_WINS: return Colour::BLACK;
        // Add other colour cases later if needed
        default: return Colour::DRAW;
    }
}

Colour ColourUtils::oppositeColour(Colour colour){
    if(colour == Colour::BLACK) return Colour::WHITE;
    return Colour::BLACK;
}
