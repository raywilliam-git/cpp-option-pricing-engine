#pragma once

#include "../options/EuropeanOption.hpp"

class BlackScholesPricer
{
public:
    double price(const EuropeanOption &option,
                 double spot,
                 double rate,
                 double volatility) const;

    double delta(const EuropeanOption &option,
                 double spot,
                 double rate,
                 double volatility) const;

    double gamma(const EuropeanOption &option,
                 double spot,
                 double rate,
                 double volatility) const;
    double vega(const EuropeanOption& option,
            double spot,
            double rate,
            double volatility) const;

private:
    double normalCDF(double x) const;
    double normalPDF(double x) const;

    double d1(const EuropeanOption &option,
              double spot,
              double rate,
              double volatility) const;

    double d2(const EuropeanOption &option,
              double spot,
              double rate,
              double volatility) const;
};