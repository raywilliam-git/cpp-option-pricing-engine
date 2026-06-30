#include <fstream>
#include <iostream>
#include <vector>

#include "../include/options/AsianOption.hpp"
#include "../include/pricers/MonteCarloPricer.hpp"

int main() {
    const double strike = 100.0;
    const double maturity = 1.0;
    const double rate = 0.05;
    const double volatility = 0.20;

    const int simulations = 100000;

    AsianOption asianCall(strike, maturity, true);
    MonteCarloPricer mcPricer;

    std::vector<int> monitoringDates = {2, 4, 40};

    std::ofstream file("results/asian_monitoring_dates.csv");

    file << "spot,time_steps,asian_price,ci_width,ci_width_percent\n";

    for (int d : monitoringDates) {
        for (double spot = 80.0; spot <= 120.0; spot += 1.0) {
            MonteCarloResult result =
                mcPricer.priceAsian(
                    asianCall,
                    spot,
                    rate,
                    volatility,
                    simulations,
                    d
                );

            double ciWidthPercent =
                100.0 * result.confidenceIntervalWidth / result.price;

            file << spot << ","
                << d << ","
                << result.price << ","
                << result.confidenceIntervalWidth << ","
                << ciWidthPercent
                << "\n";
        }

        std::cout << "Done d = " << d << std::endl;
    }

    file.close();

    std::cout << "CSV generated: results/asian_monitoring_dates.csv\n";

    return 0;
}