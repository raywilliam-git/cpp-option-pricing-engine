#pragma once

#include "Option.hpp"
#include <vector>

class AsianOption : public Option {
private:
    bool isCall;

public:
    AsianOption(double K, double T, bool isCall);

    bool getIsCall() const;

    double payoff(const std::vector<double>& path) const;
};