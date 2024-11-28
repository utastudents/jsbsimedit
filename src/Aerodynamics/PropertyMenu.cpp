#include "MenuPanel.hpp"

PropertyMenu::PropertyMenu(std::shared_ptr<AerodynamicsNode> node)
    : filterButton("Filter"),
      showAllButton("Show All"),
      okButton("OK"),
      cancelButton("Cancel"),
      m_VBox(Gtk::Orientation::VERTICAL, 10),
      currentPlaceholder(Gtk::make_managed<Gtk::Entry>()) 
{
    // Make changes to this object vvv
    this->property = std::dynamic_pointer_cast<AeroProperty>(node);
    this->setHeader("Properties");

    append(m_VBox);

    // Add container for the scrolled window and current label
    auto scrolledContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    
    // Added current label
    auto currentHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    currentLabel.set_text("Current:");
    currentLabel.set_margin(5);
    currentHBox->append(currentLabel);
}