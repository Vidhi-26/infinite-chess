#include "Player.h"

class Strategy;

class ComputerPlayer : public Player {
private:
    Strategy& strategy;
    Move getMove(const Move& move) const override;    

public:
    ComputerPlayer(Colour, Board&, Strategy&);
    virtual ~ComputerPlayer() = default;
};
