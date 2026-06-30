#include <cmath>
#include <fstream>
#include <iostream>

#include "../include/options/EuropeanOption.hpp"
#include "../include/pricers/BlackScholesPricer.hpp"
#include "../include/pricers/MonteCarloPricer.hpp"

int main() {
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    EuropeanOption call(strike, maturity, true);

    BlackScholesPricer bsPricer;
    MonteCarloPricer mcPricer;

    const double bsPrice = bsPricer.price(call, spot, rate, volatility);

    std::ofstream file("results/mc_convergence.csv");

    file << "simulations,mc_price,bs_price,ci_width,ci_lower,ci_upper,error\n";

    for (int simulations = 100; simulations <= 10000; simulations += 100) {
        MonteCarloResult result =
            mcPricer.priceEuropean(call, spot, rate, volatility, simulations);

        double halfWidth = result.confidenceIntervalWidth / 2.0;

        file << simulations << ","
             << result.price << ","
             << bsPrice << ","
             << result.confidenceIntervalWidth << ","
             << result.price - halfWidth << ","
             << result.price + halfWidth << ","
             << std::abs(result.price - bsPrice)
             << "\n";
    }

    file.close();

    std::cout << "CSV generated: results/mc_convergence.csv\n";

    return 0;
}