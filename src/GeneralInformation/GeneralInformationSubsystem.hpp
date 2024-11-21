#pragma once

#include <string>
#include "Aircraft.hpp"
#include "User.hpp"
#include "Config.hpp"
#include "inc/Subsystem.hpp"

class GeneralInformationSubsystem : public Subsystem {
public:
    GeneralInformationSubsystem();
    void Create();
    void LoadFromXML(const std::string& filePath);
    void UpdateDataFromGUI(Aircraft& aircraft, User& user, Config& config);
    void ValidateAndSave();
    void SaveToXML(const std::string& filePath, const Aircraft& aircraft, const User& user, const Config& config);

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
    Gtk::Entry m_Limitations;
    Gtk::Entry m_Notes;
};
