#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"

class MenuPanel: Gtk::Box{
private:
    std::string name;
    AerodynamicsNode::Type type;
public:
    MenuPanel();
};
