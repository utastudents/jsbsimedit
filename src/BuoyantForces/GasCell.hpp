#pragma once
#include "Ballonet.hpp"
#include "Component.hpp"

class GasCell : public Component
{
    public:
        GasCell();
        ~GasCell();
        void addBallonet(Ballonet newBallonet);
        void removeLastBallonet();
        Ballonet getBallonet(int index);
        std::vector<Ballonet> getBallonets();
        static int getBallonetCount();
        static void setBallonetCount(int count);

    private:
        std::vector<Ballonet> ballonets;
        static int ballonetCount;
};