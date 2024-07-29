#ifndef MOVE_METADATA_H
#define MOVE_METADATA_H
#include <vector>
class Piece;

class MoveMetaData {
public:
    //Meta data needed for move simulation
    char pawnPromotion;
    std::pair<Piece*, Piece*> capturedAndOriginalPawn;
    MoveMetaData(std::pair<Piece*, Piece*> capturedAndOriginalPawn, char pawnPromotion);
};

#endif  // MOVE_METADATA_H
