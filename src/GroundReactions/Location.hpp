#pragma once

class Location {
public:
    Location(double x, double y, double z);
    ~Location();

private:
    double x, y, z;
};