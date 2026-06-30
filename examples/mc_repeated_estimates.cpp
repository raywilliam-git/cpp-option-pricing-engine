#include <fstream>
#include <iostream>
#include <vector>

#include "../include/options/EuropeanOption.hpp"
#include "../include/pricers/BlackScholesPricer.hpp"
#include "../include/pricers/MonteCarloPricer.hpp"

int main() {
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    const int repetitions = 1000;

    EuropeanOption call(strike, maturity, true);

    BlackScholesPricer bsPricer;
    MonteCarloPricer mcPricer;

    double bsPrice = bsPricer.price(call, spot, rate, volatility);

    std::vector<int> simulationsList = {
        10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000
    };

    std::ofstream file("results/mc_repeated_estimates.csv");

    file << "simulations,estimate_id,mc_price,bs_price\n";

    for (int simulations : simulationsList) {
        for (int k = 0; k < repetitions; ++k) {
            MonteCarloResult result =
                mcPricer.priceEuropean(call, spot, rate, volatility, simulations);

            file << simulations << ","
                 << k << ","
                 << result.price << ","
                 << bsPrice << "\n";
        }
    }

    file.close();

    std::cout << "CSV generated: results/mc_repeated_estimates.csv\n";

    return 0;
}