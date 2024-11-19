#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"
#include <iostream>

class MenuPanel : public Gtk::Grid {
private:
    Gtk::Label* header;
public:
    MenuPanel()
    {
        set_row_spacing(10);
        set_column_spacing(10);
        // Creates a header for the menu
        header = Gtk::make_managed<Gtk::Label>();
        attach(*header,0,0);
    }
    ~MenuPanel(){}

    void setHeader(std::string title){header->set_label(title);}

    using UpdateSignal = sigc::signal<void()>;
    UpdateSignal update_signal;
};

class FunctionMenu : public MenuPanel {
public:
    FunctionMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<Function> function;
};

class TableMenu : public MenuPanel {
public:
    TableMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<Table> table;
};

class ValueMenu : public MenuPanel {
public:
    ValueMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<Value> value;
};

class AxisMenu : public MenuPanel {
public:
    AxisMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<Axis> axis;
};

class PropertyMenu : public MenuPanel {
public:
    PropertyMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<AeroProperty> property;
};