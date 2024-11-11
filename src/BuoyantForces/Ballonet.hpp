#pragma once
#include <iostream>
#include "Component.hpp"

class Ballonet : public Component
{
    public:
        Ballonet(const std::string& name, Component::GasType gastype);
        ~Ballonet();
        std::string getName();
        void inputBlowerValue(double blowerValue);
    
    private:
        std::string name;
        double blowerValue;
};