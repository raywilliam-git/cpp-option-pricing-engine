#pragma once

#include "Option.hpp"

class EuropeanOption : public Option
{
private:
    bool isCall;

public:
    EuropeanOption(double K, double T, bool isCall);

    bool getIsCall() const;

    double payoff(double spot) const;
};