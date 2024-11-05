#pragma once
#include <iostream>
#include <vector>
#include "MathFunction.hpp"

class Component
{
    public:
        Component();
        virtual ~Component() = default;
        void setLocation(double x, double y, double z);
        void setDimensions(double x, double y, double z);
        void setOverpressure(double overpressure);
        void setValveCoefficient(double valveCoefficient);
        void setInitialFullness(double initFullness);

        enum GasType {HELIUM, HYDROGEN, AIR};
        enum class Unit {
            WIDTH,              // Width
            RADIUS,             // Radius
            PSI,                // PSI
            M,                  // Meters
            IN,                 // Inches
            PA,                 // PA
            M4_SEC_KG,          // m^4 * sec / kg
            FT4_SEC_SLUG,       // ft^4 * sec / slug
            LB_FT_SEC_R,        // lb ft / (sec R)
            LBS_FT_SEC,         // lbs ft / sec
            FT3_SEC             // ft^3 / sec
        };

        static std::string unitToString(Unit unit);
        static int getBallonetCount();

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
        static int ballonetCount;
};

