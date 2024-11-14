#pragma once

#include <gtkmm.h>
#include "HierarchyPanel.hpp"
#include "MenuPanel.hpp"

class AerodynamicsWidget : public Gtk::Paned {
private:
    Gtk::Paned paned;
    HierarchyPanel hierarchyPanel;
    MenuPanel menuPanel;
public:
    AerodynamicsWidget();
};
