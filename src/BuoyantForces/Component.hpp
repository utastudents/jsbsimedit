#pragma once
#include <iostream>
#include <vector>
#include "BuoyantForces/MathFunction.hpp"

// Forward declaration of Ballonet class
class Ballonet;
class Component
{
    public:
        Component();
        virtual ~Component() = default;
        void setLocation(double x, double y, double z);
        void setDimensions(double x, double y, double z);
        void inputOverpressure(double max_overpressure);
        void inputValveCoefficient(double valveCo);
        void inputInitialFullness(double initFullness);

        enum GasType {HELIUM, HYDROGEN, AIR};

    protected:
        GasType gasType;
        double fullness;
        double overPressure;
        double location[3];
        double dimensions[3];
        double volume;
        double valveCoefficient;
        double temperature;
        double pressure;
        double mass;
        bool hasHeat;
        std::vector<MathFunction> heatFunctions;
};

class GasCell : public Component
{
    public:
        GasCell(double v, double t, double p, double m);
        ~GasCell();

    private:
        std::vector<Ballonet> ballonets;
};

class Ballonet : public Component
{
    public:
        Ballonet(const std::string& name, GasType gastype);
        ~Ballonet();
        int getBallonetNumber();
        void createBallonetTab(int tabIndex);
        void inputBlowerValue(double blowerVal);
    
    private:
        std::string name;
        int ballonetCount;
        double blowerValue;
};