#include "../../include/options/AsianOption.hpp"

#include <algorithm>

AsianOption::AsianOption(double K, double T, bool isCall)
    : Option(K, T), isCall(isCall) {}

bool AsianOption::getIsCall() const {
    return isCall;
}

double AsianOption::payoff(const std::vector<double>& path) const {
    double sum = 0.0;

    for (double spot : path) {
        sum += spot;
    }

    double averageSpot = sum / path.size();

    if (isCall) {
        return std::max(averageSpot - strike, 0.0);
    }

    return std::max(strike - averageSpot, 0.0);
}