#include "MathFunction.hpp"

MathFunction::MathFunction() {
    // Constructor
    // include any default values for attributes
}

MathFunction::~MathFunction() {
    // Destructor definition
}

void MathFunction::addFunction() {

}

void MathFunction::addProperty() {

}

void MathFunction::addValue(){

}

double MathFunction::conduction(double surfaceArea, double conductivity) {
    return surfaceArea * conductivity;


}

double MathFunction::radiation(double surfaceArea, double emissivity, double stefanConst) {
    return surfaceArea * emissivity *  stefanConst;

}

void MathFunction:: del() {

}