#include "Player.h"

class ComputerPlayer : public Player {
private:
    Strategy& strategy;
    Move getMove(const Move& move) const override;    

public:
    ComputerPlayer(Colour, Board&);
    virtual ~ComputerPlayer() = default;
};
