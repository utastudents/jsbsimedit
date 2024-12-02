#pragma once

#include <gtkmm.h>

class PointMassDialogue : public Gtk::Window {
public:
  PointMassDialogue(); // Constructor

private:
  Gtk::Box m_VBox;    // Vertical box layout
  Gtk::Label m_Label; // Label inside the popup
  Gtk::Label m_nameLabel;
  Gtk::Label m_locationLabel;
  Gtk::Label m_xLabel;
  Gtk::Label m_yLabel;
  Gtk::Label m_zLabel;
  Gtk::Label m_weightLabel;
  Gtk::Entry m_nameEntry;
  Gtk::Entry m_xEntry;
  Gtk::Entry m_yEntry;
  Gtk::Entry m_zEntry;
  Gtk::Entry m_weightEntry;
  Gtk::Button m_CloseButton; // Close button
  Gtk::ComboBoxText m_UnitDropdown;
  Gtk::ComboBoxText m_LengthDropdown;

  void on_close_button_clicked(); // Callback for the close button
};
