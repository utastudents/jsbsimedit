#include "MathFunction.hpp"
//#include "BuoyantForcesSubsystem.cpp"
#include <iostream>
/*
 int main(int argc, char const *argv[])
 {
    std::cout << "just for testing";
    return 0;
 }
*/
 

MathFunction::MathFunction() {
    // Constructor
    // include any default values for attributes
}

MathFunction::~MathFunction() {
    // Destructor definition
}

void MathFunction::addFunction(std::string function) {
    functionArray.push_back(function);
}

void MathFunction::addProperty(std::string property) {
    propertyArray.push_back(property);
}

void MathFunction::addValue(double value){
    valueArray.push_back(value);
}

void MathFunction::conduction(double surfaceArea, double conductivity) {
    double result = surfaceArea * conductivity;
    (void)result; // Suppress unused variable warning for now
}

void MathFunction::radiation(double surfaceArea, double emissivity, double stefanConst) {
    double result = surfaceArea * emissivity * stefanConst;
    (void)result; // Suppress unused variable warning for now
}


void MathFunction:: del() {

}
