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

        void setGasType(GasType type);
        void setLocationUnit(Unit type);
        void setDimensionsUnit(Unit type);
        void setDimensionsShape(Unit type);
        void setPressureUnit(Unit type);
        void setValveCoefficientUnit(Unit type);
        void setXLocation(double x);
        void setYLocation(double y);
        void setZLocation(double z);
        void setXDimension(double x);
        void setYDimension(double y);
        void setZDimension(double z);
        void setOverpressure(double overpressure);
        void setValveCoefficient(double valveCoefficient);
        void setInitialFullness(double initFullness);
        void setName(std::string newName);

        Component::GasType getGasType() const;
        Component::Unit getLocationUnit() const;
        Component::Unit getDimensionsUnit() const;
        Component::Unit getDimensionsShape() const;
        Component::Unit getPressureUnit() const;
        Component::Unit getValveCoefficientUnit() const;
        double getXLocation() const;
        double getYLocation() const;
        double getZLocation() const;
        double getXDimension() const;
        double getYDimension() const;
        double getZDimension() const;
        double getOverpressure() const;
        double getValveCoefficient() const;
        double getInitialFullness() const;
        std::string getName() const;

        static std::string unitToString(Unit unit);

    protected:
        GasType gasType;
        std::string name;
        double xLocation;
        double yLocation;
        double zLocation;
        double xDimension;
        double yDimension;
        double zDimension;
        double maxOverpressure;
        double valveCoefficient;
        double fullness;
        Unit locationUnit;
        Unit dimensionsUnit;
        Unit dimensionsShape;
        Unit pressureUnit;
        Unit valveCoefficientUnit;
        // bool hasHeat;
};

