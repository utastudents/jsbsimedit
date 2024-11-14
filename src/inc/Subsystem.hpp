#pragma once
#include <string>
#include "gtkmm.h"

// This is the definition of the interface between the main program
// and each of the subsystems.

// It is expected that it will grow over time.


class Subsystem
{
    public:
      // Every subsystem has to put all widgets on a Gtk::Grid .
      // All of the subsystem widgets are considered local to the 
      // subsystem.
      Gtk::Grid m_Grid;
      // Each subsystem has a name, that is displayed at the
      // top of the tab
      std::string m_Name;
      // some subsystems need access to the app ptr
      Glib::RefPtr<Gtk::Application> app;
      // Create makes all the widgets, and initializes and classes.
      virtual void Create() = 0;
};
