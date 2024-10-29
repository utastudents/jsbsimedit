#pragma once

class RelaxationVelocity {
public:
    RelaxationVelocity(float rolling, float side);
    ~RelaxationVelocity();

private:
    float rolling;
    float side;
};