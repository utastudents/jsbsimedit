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
 
double MathFunction::conduction(double surfaceArea, double conductivity) {
    /* double atmosphere, double temp_R
    I don't think we need to do the actual mathimatical calculations just set up so that it'll go into the XML file correctly
    */
    
    /* notes form the manual
    <function name="buoyant_forces/gas-cell/dU_conduction">
        <product>
            <value> 6282.25 </value> <!-- Surface area [ft2] -->
            <value> 0.05 </value> <!-- Conductivity [lb / (R ft sec)] -->
            <difference>
                <property> atmosphere/T-R </property>
                <property> buoyant_forces/gas-cell/temp-R </property>
            </difference>
        </product>
    </function>
    
    surfaceArea * conductivity * (atmosphere_TR - temp_R)
    */
    
    return (surfaceArea * conductivity); // - (atmosphere - temp_R)



}

double MathFunction::radiation(double surfaceArea, double emissivity, double stefanConst) {
    
    /*
    <function name="buoyant_forces/gas-cell/dU_radiation">
        <product>
            <value> 0.1714e-8 </value> <!-- Stefan-Boltzmann's constant
            [Btu / (h ft^2 R^4)] -->
            <value> 0.05 </value> <!-- Emissivity [0,1] -->
            <value> 6282.25 </value> <!-- Surface area [ft2] -->
            <difference>
                <pow>
                    <property> atmosphere/T-R </property>
                    <value> 4.0 </value>
                </pow>
                <pow>
                    <property> buoyant_forces/gas-cell/temp-R </property>
                    <value> 4.0 </value>
                </pow>
            </difference>
        </product>
    </function>
    
    stefansConstant * emissivity * surfaceArea * [(atmosphere_TR ^SomeValue ) - (temp_R ^SomeValue)]
    */
    return surfaceArea * emissivity *  stefanConst;

}

void MathFunction:: del() {

}
