#include "Player.h"

class HumanPlayer : public Player {
private:
    Move getMove(const Move& move) const override;    

public:
    HumanPlayer(Colour, Board&);
    virtual ~HumanPlayer() = default;
};
