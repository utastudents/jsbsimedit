#pragma once
#include <iostream>
#include "Component.hpp"

class Ballonet : public Component
{
    public:
        Ballonet(const std::string& name, Component::GasType gastype);
        Ballonet(const std::string& name);
        ~Ballonet();
        void setBlowerValue(double blowerValue);
        void setBlowerUnit(Component::Unit type);
        double getBlowerValue() const;
        Component::Unit getBlowerUnit() const;
    
    private:
        double blowerValue;
        Component::Unit blowerUnits;
};