#pragma once

#include <iostream>
#include <vector>
#include "MathFunction.hpp"

class Component
{
    public:
        Component();
        virtual ~Component() = default;

        enum GasType {AIR = 0, HELIUM = 1, HYDROGEN = 2};
        enum class Unit {
            /*
                Dimensions Elements
            */
            WIDTH,              // Width
            RADIUS,             // Radius

            /* 
                Max Overpressure Units
            */
            PA,                 // PA
            PSI,                // PSI

            /*
                Measurement Units (Location & ) 
                Measurement Units (Location & Dimensions) 
            */
            M,                  // Meters
            IN,                 // Inches

            /* 
                Valve Coefficient Units
            */
            FT4_SEC_SLUG,       // ft^4 * sec / slug
            M4_SEC_KG,          // m^4 * sec / kg
            
            /*
                Heat Transfer Coefficent Units
            */
            LBS_FT_SEC,         // lbs ft / sec
            LB_FT_SEC_R,        // lb ft / (sec R)

            /* 
                Blower Input Units
            */
            FT3_SEC            // ft^3 / sec
        };

        void setLocation(double locationX, double locationY, double locationZ);
        void setDimensions(double x, double y, double z);
        void setOverpressure(double overpressure);
        void setValveCoefficient(double valveCoefficient);
        void setInitialFullness(double initFullness);

        static std::string unitToString(Unit unit);
        static int getBallonetCount();
        static void setBallonetCount(int count);

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

