#pragma once

#include <gtkmm.h>

class MenuPanel: gtkmm::box{
private:
    std::string name;
    AerodynamicsNode::Type type;
public:
    MenuPanel();
};