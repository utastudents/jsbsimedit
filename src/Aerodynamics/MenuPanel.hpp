#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"

class MenuPanel : public Gtk::Box {
private:
    Gtk::Label name;
    AerodynamicsNode::Type type;

public:
    MenuPanel();
};

