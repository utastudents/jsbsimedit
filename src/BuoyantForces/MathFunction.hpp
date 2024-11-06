#pragma once
#include <iostream>
#include <vector>

class MathFunction
{
    public:
        MathFunction();
        ~MathFunction();
        void addFunction(std::string function);
        void addProperty(std::string property);
        void addValue(double value);
        void radiation(double emissivity, double surfaceArea, double stefanConst);
        void conduction(double surfaceArea, double conductivity);
        void del();     // delete method

    private:
        std::string name;
        std::string description;
        std::vector<std::string> dropDownMenu;
        std::vector<std::string> functionArray;
        std::vector<std::string> propertyArray;
        std::vector<double> valueArray;
};
