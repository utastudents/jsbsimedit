#pragma once
#include <iostream>
#include <vector>
#include "Component.hpp"

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