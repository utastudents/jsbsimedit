#pragma once

#include <string>

class DampingCoefficient {
public:
    DampingCoefficient(double value, const std::string& unit = "LBS/FT/SEC");
    ~DampingCoefficient();

private:
    double value;
    std::string unit;
};