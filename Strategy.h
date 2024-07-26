#ifndef STRATEGY_H
#define STRATEGY_H

class Move;

class Strategy {
private:
    virtual Move getStrategyImpl() const = 0;

public:
    Strategy();
    virtual ~Strategy() = default;
    Move getStrategy() const;
};

#endif