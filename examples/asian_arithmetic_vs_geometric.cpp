#include <fstream>
#include <iostream>

#include "../include/options/AsianOption.hpp"
#include "../include/pricers/MonteCarloPricer.hpp"

int main() {
    const double strike = 100.0;
    const double maturity = 1.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    const int simulations = 100000;
    const int timeSteps = 40;

    AsianOption asianCall(strike, maturity, true);
    MonteCarloPricer mcPricer;

    std::ofstream file("results/asian_arithmetic_vs_geometric.csv");

    file << "spot,arithmetic_price,arithmetic_ci_width,geometric_price,geometric_ci_width\n";

    for (double spot = 80.0; spot <= 120.0; spot += 1.0) {
        MonteCarloResult arithmeticResult =
            mcPricer.priceAsian(
                asianCall,
                spot,
                rate,
                volatility,
                simulations,
                timeSteps
            );

        MonteCarloResult geometricResult =
            mcPricer.priceGeometricAsian(
                asianCall,
                spot,
                rate,
                volatility,
                simulations,
                timeSteps
            );

        file << spot << ","
             << arithmeticResult.price << ","
             << arithmeticResult.confidenceIntervalWidth << ","
             << geometricResult.price << ","
             << geometricResult.confidenceIntervalWidth
             << "\n";

        std::cout << "Done spot = " << spot << std::endl;
    }

    file.close();

    std::cout << "CSV generated: results/asian_arithmetic_vs_geometric.csv\n";

    return 0;
}