#pragma once
#include "inc/Subsystem.hpp"

class GeneralInformationSubsystem : public Subsystem {
public:
    GeneralInformationSubsystem();
    void Create();

private:
    // Define attributes to hold references to input widgets
    Gtk::Entry m_AircraftNameEntry;
    Gtk::Entry m_FileNameEntry;
    Gtk::Entry m_ReleaseLevelEntry;
    Gtk::Entry m_ConfigVersionEntry;
    Gtk::Entry m_FlightModelVersionEntry;
    Gtk::Entry m_AuthorEntry;
    Gtk::Entry m_EmailEntry;
    Gtk::Entry m_OrganizationEntry;
};
