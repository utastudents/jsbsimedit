#pragma once
#include "gtkmm.h"
// This is the definition of the interface between the main program
// and each of the subsystems.

// It is expected that it will grow over time.


class Subsystem
{
    public:
      Gtk::Grid m_Grid;
      // Every subsystem has to put all widgets on a Gtk::Grid .
      // All of the subsystem widgets are considered local to the 
      // subsystem.
      virtual void Create() = 0;
      // Create makes all the widgets, and initializes and classes.
};
