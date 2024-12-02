#include "FilterComponentWindow.hpp"

namespace DragDrop {

FilterComponentWindow::FilterComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                                             std::shared_ptr<std::set<std::string>> setOfNames)
    : ComponentWindowCommon(comp, setOfNames) {
    CreateCommonTab();
    FilterTab();
}

void FilterComponentWindow::FilterTab() {
    Gtk::Grid grid;
    grid.set_margin_top(10);
    grid.set_margin_start(10);

    // FC-6, FC-7: Labels for "Name", "Type", etc.
    Gtk::Label nameLabel{"Name:"};
    Gtk::Entry nameEntry;
    grid.attach(nameLabel, 0, 0);
    grid.attach(nameEntry, 1, 0);

    Gtk::Label typeLabel{"Type:"};
    Gtk::ComboBoxText typeDropdown;
    typeDropdown.append("Default");
    typeDropdown.append("Custom");
    grid.attach(typeLabel, 0, 1);
    grid.attach(typeDropdown, 1, 1);

    Gtk::Label orderLabel{"Order:"};
    Gtk::Entry orderEntry;
    grid.attach(orderLabel, 0, 2);
    grid.attach(orderEntry, 1, 2);

    // FC-8, FC-10: Text entries for numerical inputs
    Gtk::Label maxLabel{"Max:"};
    Gtk::Entry maxEntry;
    grid.attach(maxLabel, 0, 3);
    grid.attach(maxEntry, 1, 3);

    Gtk::Label minLabel{"Min:"};
    Gtk::Entry minEntry;
    grid.attach(minLabel, 0, 4);
    grid.attach(minEntry, 1, 4);

    // FC-21: Checkbox for enabling/disabling filter
    Gtk::CheckButton enableButton{"Enable"};
    grid.attach(enableButton, 0, 5);

    m_noteBook.append_page(grid, "Filter");
}

void FilterComponentWindow::SaveInfo() {
    // Save the current state to the component
}

void FilterComponentWindow::CancelInfo() {
    // Close without saving
}

} // namespace DragDrop