#include "ComputerPlayer.h"
#include "Strategy.h"

ComputerPlayer::ComputerPlayer(Colour colour, Board& board, Strategy& strategy) : Player{colour, board}, strategy{strategy} {}

Move ComputerPlayer::getMove(const Move& move) const {
    return strategy.getStrategy(board, colour);
}
