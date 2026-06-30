#include <iostream>
#include "include/options/EuropeanOption.hpp"
#include "include/options/AsianOption.hpp"

#include "include/pricers/BlackScholesPricer.hpp"
#include "include/pricers/MonteCarloPricer.hpp"

int main() {
    EuropeanOption call(100.0, 1.0, true);
    EuropeanOption put(100.0, 1.0, false);

    double spot = 100.0;
    double rate = 0.05;
    double volatility = 0.20;

    BlackScholesPricer pricer;

    std::cout << "Call price = "
            << pricer.price(call, spot, rate, volatility)
            << std::endl;

    std::cout << "Put price = "
            << pricer.price(put, spot, rate, volatility)
            << std::endl;

    std::cout << "Call delta = "
            << pricer.delta(call, spot, rate, volatility)
            << std::endl;

    std::cout << "Call gamma = "
            << pricer.gamma(call, spot, rate, volatility)
            << std::endl;

    std::cout << "Call vega = "
            << pricer.vega(call, spot, rate, volatility)
            << std::endl;

    MonteCarloPricer mcPricer;

    MonteCarloResult mcResult =
        mcPricer.priceEuropean(call, spot, rate, volatility, 100000);

    std::cout << "Monte Carlo call price = "
            << mcResult.price
            << std::endl;

    std::cout << "95% confidence interval width = "
            << mcResult.confidenceIntervalWidth
            << std::endl;

    // TP2

    AsianOption asianCall(100.0, 1.0, true);

    MonteCarloResult asianResult =
        mcPricer.priceAsian(
            asianCall,
            spot,
            rate,
            volatility,
            100000,
            252
        );

    std::cout << "Asian Call price = "
            << asianResult.price
            << std::endl;

    std::cout << "Asian 95% confidence interval width = "
            << asianResult.confidenceIntervalWidth
            << std::endl;


        MonteCarloResult geometricResult =
        mcPricer.priceGeometricAsian(
            asianCall,
            spot,
            rate,
            volatility,
            100000,
            252
        );

    std::cout << "Geometric Asian Call price = "
            << geometricResult.price
            << std::endl;

    std::cout << "Geometric Asian CI width = "
            << geometricResult.confidenceIntervalWidth
            << std::endl;

    return 0;
}