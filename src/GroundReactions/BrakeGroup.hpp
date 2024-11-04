#pragma once

#include <string>

class BrakeGroup {
public:
    BrakeGroup(const std::string& name);
    ~BrakeGroup();

private:
    std::string name;
};