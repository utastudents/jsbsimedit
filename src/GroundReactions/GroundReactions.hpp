#pragma once

#include <vector>
#include "Contact.hpp"

class GroundReactions {
public:
    GroundReactions();
    ~GroundReactions();
    void draw();

private:
    std::vector<Contact> contacts;
};