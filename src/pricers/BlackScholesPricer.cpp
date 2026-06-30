#include "../../include/pricers/BlackScholesPricer.hpp"
#include <cmath>

double BlackScholesPricer::normalCDF(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double BlackScholesPricer::normalPDF(double x) const {
    static const double inv_sqrt_2pi = 0.3989422804014327;
    return inv_sqrt_2pi * std::exp(-0.5 * x * x);
}

double BlackScholesPricer::d1(const EuropeanOption& option,
                              double spot,
                              double rate,
                              double volatility) const {
    double K = option.getStrike();
    double T = option.getMaturity();

    return (std::log(spot / K) + (rate + 0.5 * volatility * volatility) * T)
           / (volatility * std::sqrt(T));
}

double BlackScholesPricer::d2(const EuropeanOption& option,
                              double spot,
                              double rate,
                              double volatility) const {
    return d1(option, spot, rate, volatility)
           - volatility * std::sqrt(option.getMaturity());
}

double BlackScholesPricer::price(const EuropeanOption& option,
                                 double spot,
                                 double rate,
                                 double volatility) const {
    double K = option.getStrike();
    double T = option.getMaturity();

    double d_1 = d1(option, spot, rate, volatility);
    double d_2 = d2(option, spot, rate, volatility);

    if (option.getIsCall()) {
        return spot * normalCDF(d_1)
               - K * std::exp(-rate * T) * normalCDF(d_2);
    }

    return K * std::exp(-rate * T) * normalCDF(-d_2)
           - spot * normalCDF(-d_1);
}

double BlackScholesPricer::delta(const EuropeanOption& option,
                                 double spot,
                                 double rate,
                                 double volatility) const {
    double d_1 = d1(option, spot, rate, volatility);

    if (option.getIsCall()) {
        return normalCDF(d_1);
    }

    return normalCDF(d_1) - 1.0;
}

double BlackScholesPricer::gamma(const EuropeanOption& option,
                                 double spot,
                                 double rate,
                                 double volatility) const {
    double d_1 = d1(option, spot, rate, volatility);
    double T = option.getMaturity();

    return normalPDF(d_1) / (spot * volatility * std::sqrt(T));
}

double BlackScholesPricer::vega(const EuropeanOption& option,
                                double spot,
                                double rate,
                                double volatility) const {
    double d_1 = d1(option, spot, rate, volatility);
    double T = option.getMaturity();

    return spot * normalPDF(d_1) * std::sqrt(T);
}