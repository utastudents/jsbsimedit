#pragma once
#include <vector>
#include <string>

namespace DragDrop
{

enum ComponentType
{
    ACTUATOR=0, DEADBAND, DESTINATION, FILTER, FUNC, GAIN, KINEMATIC, PID, SENSOR, SOURCE, SUMMER, SWITCH
};

//Forgive this sin please -phil c
inline const std::vector<std::string> COMPONENT_NAMES { "actuator", "deadband", 
        "destination", "filter", "func", "gain", "kinemat"
        , "pid", "sensor", "source", "summer", "switch"
};

};

