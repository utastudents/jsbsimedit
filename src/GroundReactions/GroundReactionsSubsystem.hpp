#pragma once

#include "inc/Subsystem.hpp"
#include "gtkmm.h"
#include <vector>
#include "Contact.hpp"

class GroundReactionsSubsystem : public Subsystem {
public:
    GroundReactionsSubsystem(); // deleted destructor
    void Create();

private:
    std::vector<Contact> contacts;
};