#pragma once

#include <string>

class SpringCoefficient {
public:
    SpringCoefficient(double value, const std::string& unit = "LBS/FT");
    ~SpringCoefficient();

private:
    double value;
    std::string unit;
};