#include "PointMassDialogue.hpp"

PointMassDialogue::PointMassDialogue()
    : m_VBox(Gtk::Orientation::VERTICAL), m_Label("Properties of Pointmass"),
      m_CloseButton("Close"), m_nameLabel("Name:"), m_locationLabel("Location"),
      m_xLabel("x="), m_yLabel("y="), m_zLabel("z="), m_weightLabel("Weight"),
      m_UnitDropdown(), m_LengthDropdown() {
  // Set the window properties
  set_default_size(600, 400);
  set_title("New Point Mass");

  // Add the VBox layout to the window
  set_child(m_VBox);

  // Add the label and button to the VBox
  m_VBox.append(m_Label);

  m_VBox.append(m_nameLabel);
  m_VBox.append(m_nameEntry);
  m_VBox.append(m_locationLabel);
  m_VBox.append(m_xLabel);
  m_VBox.append(m_xEntry);
  m_VBox.append(m_yLabel);
  m_VBox.append(m_yEntry);
  m_VBox.append(m_zLabel);
  m_VBox.append(m_zEntry);
  m_LengthDropdown.append("in");
  m_LengthDropdown.append("cm");
  m_LengthDropdown.set_active(0);
  m_VBox.append(m_LengthDropdown);
  m_VBox.append(m_weightLabel);
  m_VBox.append(m_weightEntry);
  m_UnitDropdown.append("lbs");
  m_UnitDropdown.append("kgs");
  m_UnitDropdown.set_active(0);
  m_VBox.append(m_UnitDropdown);

  m_VBox.append(m_CloseButton);

  // Connect the close button signal
  m_CloseButton.signal_clicked().connect(
      sigc::mem_fun(*this, &PointMassDialogue::on_close_button_clicked));
}

void PointMassDialogue::on_close_button_clicked() {
  hide(); // Close the window
}