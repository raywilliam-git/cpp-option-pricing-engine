#include "../../include/pricers/MonteCarloPricer.hpp"

#include <cmath>
#include <random>
#include <vector>

MonteCarloResult MonteCarloPricer::priceEuropean(const EuropeanOption& option,
                                                double spot,
                                                double rate,
                                                double volatility,
                                                int simulations,
                                                double alpha) const {
    static std::mt19937 generator(42);
    std::normal_distribution<double> normal(0.0, 1.0);

    double K = option.getStrike();
    double T = option.getMaturity();

    std::vector<double> discountedPayoffs;
    discountedPayoffs.reserve(simulations);

    double sum = 0.0;

    for (int i = 0; i < simulations; ++i) {
        double Z = normal(generator);

        double terminalSpot =
            spot * std::exp((rate - 0.5 * volatility * volatility) * T
                            + volatility * std::sqrt(T) * Z);

        double payoff = option.payoff(terminalSpot);
        double discountedPayoff = std::exp(-rate * T) * payoff;

        discountedPayoffs.push_back(discountedPayoff);
        sum += discountedPayoff;
    }

    double price = sum / simulations;

    double variance = 0.0;

    for (double x : discountedPayoffs) {
        variance += (x - price) * (x - price);
    }

    variance /= (simulations - 1);

    // alpha = 0.05 -> 95% confidence interval.
    // We use 1.96 as the normal quantile.
    double normalQuantile = 1.96;

    double confidenceIntervalWidth =
        2.0 * normalQuantile * std::sqrt(variance / simulations);

    return {price, confidenceIntervalWidth};
}

MonteCarloResult MonteCarloPricer::priceAsian(const AsianOption& option,
                                              double spot,
                                              double rate,
                                              double volatility,
                                              int simulations,
                                              int timeSteps,
                                              double alpha) const {
    static std::mt19937 generator(123);
    std::normal_distribution<double> normal(0.0, 1.0);

    double T = option.getMaturity();
    double dt = T / timeSteps;

    std::vector<double> discountedPayoffs;
    discountedPayoffs.reserve(simulations);

    double sum = 0.0;

    for (int i = 0; i < simulations; ++i) {
        std::vector<double> path;
        path.reserve(timeSteps);

        double currentSpot = spot;

        for (int j = 0; j < timeSteps; ++j) {
            double Z = normal(generator);

            currentSpot *= std::exp(
                (rate - 0.5 * volatility * volatility) * dt
                + volatility * std::sqrt(dt) * Z
            );

            path.push_back(currentSpot);
        }

        double payoff = option.payoff(path);
        double discountedPayoff = std::exp(-rate * T) * payoff;

        discountedPayoffs.push_back(discountedPayoff);
        sum += discountedPayoff;
    }

    double price = sum / simulations;

    double variance = 0.0;

    for (double x : discountedPayoffs) {
        variance += (x - price) * (x - price);
    }

    variance /= (simulations - 1);

    double normalQuantile = 1.96;

    double confidenceIntervalWidth =
        2.0 * normalQuantile * std::sqrt(variance / simulations);

    return {price, confidenceIntervalWidth};
}


MonteCarloResult MonteCarloPricer::priceGeometricAsian(const AsianOption& option,
                                                       double spot,
                                                       double rate,
                                                       double volatility,
                                                       int simulations,
                                                       int timeSteps,
                                                       double alpha) const {
    static std::mt19937 generator(456);
    std::normal_distribution<double> normal(0.0, 1.0);

    double T = option.getMaturity();
    double dt = T / timeSteps;

    std::vector<double> discountedPayoffs;
    discountedPayoffs.reserve(simulations);

    double sum = 0.0;

    for (int i = 0; i < simulations; ++i) {
        double currentSpot = spot;
        double logSum = 0.0;

        for (int j = 0; j < timeSteps; ++j) {
            double Z = normal(generator);

            currentSpot *= std::exp(
                (rate - 0.5 * volatility * volatility) * dt
                + volatility * std::sqrt(dt) * Z
            );

            logSum += std::log(currentSpot);
        }

        double geometricAverage = std::exp(logSum / timeSteps);

        double payoff;
        if (option.getIsCall()) {
            payoff = std::max(geometricAverage - option.getStrike(), 0.0);
        } else {
            payoff = std::max(option.getStrike() - geometricAverage, 0.0);
        }

        double discountedPayoff = std::exp(-rate * T) * payoff;

        discountedPayoffs.push_back(discountedPayoff);
        sum += discountedPayoff;
    }

    double price = sum / simulations;

    double variance = 0.0;

    for (double x : discountedPayoffs) {
        variance += (x - price) * (x - price);
    }

    variance /= (simulations - 1);

    double normalQuantile = 1.96;

    double confidenceIntervalWidth =
        2.0 * normalQuantile * std::sqrt(variance / simulations);

    return {price, confidenceIntervalWidth};
}