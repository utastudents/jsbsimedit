#pragma once
#include "Ballonet.hpp"
#include "Component.hpp"

class GasCell : public Component
{
    public:
        GasCell();
        ~GasCell();

    private:
        std::vector<Ballonet> ballonets;
};