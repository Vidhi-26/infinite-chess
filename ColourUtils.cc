#include "ColourUtils.h"

std::string ColourUtils::toString(Colour colour) {
    switch (colour) {
        case Colour::WHITE: return "White";
        case Colour::BLACK: return "Black";
        // Add other colour cases later if needed
        default: return "Unknown Colour";
    }
}
