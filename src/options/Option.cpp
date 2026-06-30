#include "../../include/options/Option.hpp"

// Constructor
Option::Option(double K, double T)
    : strike(K), maturity(T) {}

// Getter for strike
double Option::getStrike() const
{
    return strike;
}

// Getter for maturity
double Option::getMaturity() const
{
    return maturity;
}