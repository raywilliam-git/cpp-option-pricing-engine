#include <fstream>
#include <iostream>
#include <vector>

#include "../include/options/EuropeanOption.hpp"
#include "../include/pricers/BlackScholesPricer.hpp"

int main() {
    const double strike = 100.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    std::vector<double> maturities = {0.05, 0.1, 0.2, 0.5, 1.0, 2.0};

    BlackScholesPricer pricer;

    std::ofstream file("results/bs_price_greeks_vs_spot.csv");

    file << "spot,maturity,price,delta,gamma,vega,payoff\n";

    for (double T : maturities) {
        EuropeanOption call(strike, T, true);

        for (double spot = 80.0; spot <= 120.0; spot += 0.5) {
            file << spot << ","
                 << T << ","
                 << pricer.price(call, spot, rate, volatility) << ","
                 << pricer.delta(call, spot, rate, volatility) << ","
                 << pricer.gamma(call, spot, rate, volatility) << ","
                 << pricer.vega(call, spot, rate, volatility) << ","
                 << call.payoff(spot)
                 << "\n";
        }
    }

    file.close();

    std::cout << "CSV generated: results/bs_price_greeks_vs_spot.csv\n";

    return 0;
}