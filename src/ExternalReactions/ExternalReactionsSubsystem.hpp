#pragma once
#include "gtkmm.h"
#include "inc/Subsystem.hpp"
#include "ExternalForce.hpp"  // Include the Force class

class ExternalReactionsSubsystem : public Subsystem {
public:
    ExternalReactionsSubsystem();
    void Create();
    void tabSetup(Gtk::Grid& ex_grid);

protected:
    Gtk::Notebook m_notebook;
    std::vector<std::unique_ptr<Gtk::Grid>> m_pages;
    std::map<std::string, std::unique_ptr<Gtk::DropDown>> m_dropdown;
    Glib::RefPtr<Gtk::StringList> m_unitList;

private:
    double locationX;
    double locationY;
    double locationZ;
    double directionX;
    double directionY;
    double directionZ;
    Gtk::Entry* m_nameTextbox;
    int m_forceCount;

    // Add a member to store the current Force object
    Force m_currentForce;
};
