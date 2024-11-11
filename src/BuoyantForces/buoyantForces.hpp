#pragma once

#include "GasCell.hpp"
#include "Ballonet.hpp"

class BuoyantForces 
{
    public:
        void getGasCell();
        void getBallonet();
        void getHeat();
        void getBlower();

    private:
        GasCell gasCell;
        int numBallonets;
        Ballonet ballonet;
};