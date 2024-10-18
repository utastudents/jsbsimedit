#pragma once
#include <iostream>
#include <vector>

class GasCell
{
    public:
        GasCell(double v, double t, double p, double m, int g);
        ~GasCell();
        double getTemperature();
        double getVolume();
        double getPressure();
        double getMass();
        int getGasCellIndex();

    private:
        double volume;
        double temperature;
        double pressure;
        double mass;
        int gasCellIndex;
};

class Ballonet
{
    public:
        int getBallonetNumber();
        void createBallonetTab(int tabIndex);
        void createBallonet(const std::string& name, const std::string& gasType);
        void selectMeasurementUnits(const std::string& unit);
        void setLocation(double x, double y, double z);
        void setDimensions(double x, double y, double z);
        void inputOverpressure(double overpressure);
        void inputValveCoefficient(double vlaveCoefficient);
        void inputInitialFullness(double fullness);
        void inputBlowerValve(double blowerValue);
    
    private:
        int ballonetCount;
        std::string gasType;
        double location[3];
        double dimensions[3];
        double volume;
        double temperature;
        double pressure;
        double mass;
        double fullness;
        double blowerValue;
};

class MathFunction
{
    public:
        MathFunction();
        ~MathFunction();
        void addFunction();
        void addProperty();
        void addValue();
        void delFunction();
        void delProperty();
        void delValue();

    private:
    std::string name;
    std::string description;
    std::vector<std::string> functionArray;
    std::vector<std::string> propertyArray;
    std::vector<int> valueArray;

};