#pragma once

#include <string>

class MaxSteer {
public:
    MaxSteer(double value, const std::string& unit = "DEG");
    ~MaxSteer();

private:
    double value;
    std::string unit;
};