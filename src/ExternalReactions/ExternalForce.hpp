#pragma once 
#include <iostream>
using namespace std;

enum Frame {BODY,LOCAL,WIND};

class Force{
    public: 
        struct forceVector{
            float x,y,z;
            forceVector(float x_val = 0, float y_val = 0, float z_val = 0);
        };
        Force(forceVector direction = forceVector(), forceVector location = forceVector());
        ~Force();
        void applyForce();
        string forceName(string name);
        double locationUnits(double units);
        void changeFrame(Frame newFrame);
    private:
        forceVector Location;
        forceVector Direction;
        Frame frameType;  
        string name;
        double units;
};