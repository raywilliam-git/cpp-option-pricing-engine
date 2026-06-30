#pragma once

class Option
{
protected:
    double strike;
    double maturity;

public:
    Option(double K, double T);

    virtual ~Option() = default;

    double getStrike() const;
    double getMaturity() const;
};