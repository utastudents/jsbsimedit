#pragma once

#include "inc/Subsystem.hpp"
#include "gtkmm.h"
#include <vector>
#include "Contact.hpp"

class GroundReactionsSubsystem : public Subsystem {
public:
    GroundReactionsSubsystem();
    void Create();

private:
    std::vector<Contact> contacts;

    class LandingGearSetupDialog : public Gtk::Dialog {
    public: 
        LandingGearSetupDialog(
        const std::string& contactName, 
        const std::string& contactType,
        const std::tuple<double, double, double>& locationCoordinates, 
        const std::string& locationUnit,
        const std::string& brakeGroup,
        const std::string& springCoefficient, 
        const std::string& dampingCoefficient, 
        const std::string& staticFriction, 
        const std::string& dynamicFriction, 
        const std::string& rollingFriction, 
        const std::string& maxSteer,
        const std::string& retractable
        );
    };
};