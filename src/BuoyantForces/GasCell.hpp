#pragma once
#include "Ballonet.hpp"
#include "Component.hpp"

class GasCell : public Component
{
    public:
        GasCell(double v, double t, double p, double m);
        ~GasCell();

    private:
        std::vector<Ballonet> ballonets;
};