#include <fstream>
#include <iostream>

#include "../include/options/EuropeanOption.hpp"
#include "../include/options/AsianOption.hpp"

#include "../include/pricers/BlackScholesPricer.hpp"
#include "../include/pricers/MonteCarloPricer.hpp"

int main() {
    const double strike = 100.0;
    const double maturity = 1.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    const int simulations = 100000;
    const int timeSteps = 252;

    BlackScholesPricer bsPricer;
    MonteCarloPricer mcPricer;

    std::ofstream file("results/asian_vs_european.csv");

    file << "spot,european_price,asian_price,asian_ci_width\n";

    for (double spot = 80.0; spot <= 120.0; spot += 1.0) {
        EuropeanOption europeanCall(strike, maturity, true);
        AsianOption asianCall(strike, maturity, true);

        double europeanPrice =
            bsPricer.price(europeanCall, spot, rate, volatility);

        MonteCarloResult asianResult =
            mcPricer.priceAsian(
                asianCall,
                spot,
                rate,
                volatility,
                simulations,
                timeSteps
            );

        file << spot << ","
             << europeanPrice << ","
             << asianResult.price << ","
             << asianResult.confidenceIntervalWidth
             << "\n";

        std::cout << "Done spot = " << spot << std::endl;
    }

    file.close();

    std::cout << "CSV generated: results/asian_vs_european.csv\n";

    return 0;
}