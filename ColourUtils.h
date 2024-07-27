#ifndef COLOUR_UTILS_H
#define COLOUR_UTILS_H
#include <string>
#include "Colour.h"
#include "GameState.h"

// enum class Colour;

class ColourUtils {
public:
    static std::string toString(Colour);
    static Colour getWinner(GameState gs);
};

#endif  // COLOUR_UTILS_H
