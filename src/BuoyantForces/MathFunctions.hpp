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