#pragma once
#include <iostream>
#include <vector>
#include "BuoyantForces/MathFunctions.hpp"

class Component
{
    public:
        virtual ~Component() = default;
        void setLocation(double x, double y, double z);
        void setDimensions(double x, double y, double z);
        void inputOverpressure(double overpressure);
        void inputValveCoefficient(double valveCoefficient);
        void inputInitialFullness(double fullness);
        void selectMeasurementUnits(const std::string& unit);

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
        GasCell(double v, double t, double p, double m, int g);
        ~GasCell();

    private:
        std::vector<Ballonet> ballonets;
};

class Ballonet : public Component
{
    public:
        // Constructor Missing

        ~Ballonet();
        int getBallonetNumber();
        void createBallonetTab(int tabIndex);
        void createBallonet(const std::string& name, const std::string& gasType);
        void inputBlowerValve(double blowerValue);
    
    private:
        std::string name;
        int ballonetCount;
        double blowerValue;
};