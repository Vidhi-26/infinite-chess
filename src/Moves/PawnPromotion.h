#ifndef PAWN_PROMOTION_H
#define PAWN_PROMOTION_H
#include <utility>
#include <functional>
#include "AbstractMove.h"

class PawnPromotion : AbstractMove {
private:
    char pawnPromotion;
    
public:
    PawnPromotion(int = -1, int = -1, int = -1, int = -1, char = ' ');
    PawnPromotion(std::pair<int, int>, std::pair<int, int>, char = ' ');
    virtual ~PawnPromotion() = default;

    void addPawnPromotion(char);
    char getPawnPromotion() const;

    bool operator==(const PawnPromotion& move) const;
};

#endif  // PAWN_PROMOTION_H
