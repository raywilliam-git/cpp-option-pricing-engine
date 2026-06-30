#pragma once

#include "../options/EuropeanOption.hpp"
#include "../options/AsianOption.hpp"

struct MonteCarloResult {
    double price;
    double confidenceIntervalWidth;
};

class MonteCarloPricer {
public:
    MonteCarloResult priceEuropean(const EuropeanOption& option,
                                double spot,
                                double rate,
                                double volatility,
                                int simulations,
                                double alpha = 0.05) const;
    MonteCarloResult priceAsian(const AsianOption& option,
                            double spot,
                            double rate,
                            double volatility,
                            int simulations,
                            int timeSteps,
                            double alpha = 0.05) const;
    MonteCarloResult priceGeometricAsian(const AsianOption& option,
                            double spot,
                            double rate,
                            double volatility,
                            int simulations,
                            int timeSteps,
                            double alpha = 0.05) const;
};