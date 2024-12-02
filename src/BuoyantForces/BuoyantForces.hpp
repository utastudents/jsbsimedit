#pragma once

#include "GasCell.hpp"
#include "Ballonet.hpp"

class BuoyantForces 
{
    public:
        BuoyantForces();
        void setHasBuoyantForces(bool byfActive);
        void setGasCell(GasCell newGasCell);
        bool isBuoyantForcesActive();
        GasCell getGasCell();

    private:
        bool hasBuoyantForces;
        GasCell gasCell;
};