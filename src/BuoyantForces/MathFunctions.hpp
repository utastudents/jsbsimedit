#pragma once
#include <iostream>
#include <vector>

class MathFunction
{
    public:
        MathFunction();
        ~MathFunction();
        void addFunction();
        void addProperty();
        void addValue();
        double radiation(double emissivity, double surfaceArea, double stefanConst);
        double conduction(double surfaceArea, double conductivity);
        void del();     // delete method

    private:
        std::string name;
        std::string description;
        std::string dropDownMenu;
        std::vector<std::string> functionArray;
        std::vector<std::string> propertyArray;
        std::vector<double> valueArray;
};