#include "../../include/options/EuropeanOption.hpp"
#include <algorithm>

// Constructor
EuropeanOption::EuropeanOption(double K,
                               double T,
                               bool isCall)
    : Option(K, T), isCall(isCall) {}

// Getter
bool EuropeanOption::getIsCall() const
{
    return isCall;
}

// Payoff function
double EuropeanOption::payoff(double spot) const
{

    // Call option
    if (isCall)
    {
        return std::max(spot - strike, 0.0);
    }

    // Put option
    return std::max(strike - spot, 0.0);
}