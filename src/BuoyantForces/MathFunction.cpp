#include "MathFunction.hpp"
#include <iostream>

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

double MathFunction::conduction(double surfaceArea, double conductivity) {
    return surfaceArea * conductivity;


}

double MathFunction::radiation(double surfaceArea, double emissivity, double stefanConst) {
    return surfaceArea * emissivity *  stefanConst;

}

void MathFunction:: del() {

}