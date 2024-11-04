#pragma once

#include <string>
#include <memory>
#include "Location.hpp"
#include "SpringCoefficient.hpp"
#include "DampingCoefficient.hpp"
#include "MaxSteer.hpp"
#include "BrakeGroup.hpp"
#include "RelaxationVelocity.hpp"
#include "ForceLagFilter.hpp"

class Contact {
public:
    Contact(const std::string& name, const std::string& type);
    ~Contact();
    enum GEARTYPE {BOGEY, STRUCTURE};

private:
    std::string name;
    std::string type;
    Location location;
    double staticFriction;
    double dynamicFriction;
    std::unique_ptr<SpringCoefficient> springCoeff;
    std::unique_ptr<DampingCoefficient> dampingCoeff;
    std::unique_ptr<DampingCoefficient> dampingCoeffRebound;
    double rollingFriction;
    std::unique_ptr<MaxSteer> maxSteer;
    std::unique_ptr<BrakeGroup> brakeGroup;
    std::unique_ptr<int> retractable;
    std::unique_ptr<RelaxationVelocity> relaxationVelocity;
    std::unique_ptr<ForceLagFilter> forceLagFilter;
    float wheelSlipFilter;
};