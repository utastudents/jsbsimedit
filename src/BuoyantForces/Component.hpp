#pragma once
#include <iostream>
#include <vector>
#include "MathFunction.hpp"

// Forward declaration of Ballonet class
class Ballonet;
class Component
{
    public:
        Component();
        virtual ~Component() = default;
        void setLocation(double x, double y, double z);
        void setDimensions(double x, double y, double z);
        void inputOverpressure(double overpressure);
        void inputValveCoefficient(double valveCoefficient);
        void inputInitialFullness(double initFullness);

        enum GasType {HELIUM, HYDROGEN, AIR};

    protected:
        GasType gasType;
        double location[3];
        double dimensions[3];
        double maxOverpressure;
        double fullness;
        double valveCoefficient;
        double volume;
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
        void inputBlowerValue(double blowerValue);
    
    private:
        std::string name;
        int ballonetCount;
        double blowerValue;
};