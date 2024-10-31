#pragma once

class ForceLagFilter {
public:
    ForceLagFilter(float rolling, float side);
    ~ForceLagFilter();

private:
    float rolling;
    float side;
};