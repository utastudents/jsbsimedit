#pragma once 
#include <iostream>

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
        void calculateMagnitude();
        void changeFrame(Frame newFrame);
    private:
        forceVector Location;
        forceVector Direction;
        Frame frameType;  
};