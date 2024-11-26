#include "FilterComponent.hpp"

namespace DragDrop {

FilterComponentWindow::FilterComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                                             std::shared_ptr<std::set<std::string>> setOfNames)
    : ComponentWindowCommon(comp, setOfNames) {
    CreateCommonTab();
    CreateFilterTab();
}

void FilterComponentWindow::CreateFilterTab() {
    Gtk::Box container;
    container.set_vexpand(true);
    container.set_hexpand(true);

    Gtk::Grid grid{};
    grid.set_margin_top(15);
    grid.set_hexpand(true);
    grid.set_vexpand(true);

    // Scrollable area
    Gtk::ScrolledWindow scrolled;
    scrolled.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolled.set_child(grid);
    container.append(scrolled);

    // Title
    Gtk::Label title{"Filter Component"};
    grid.attach(title, 0, 0, 2);

    // Name input (FC-8)
    Gtk::Label nameLabel{"Name:"};
    Gtk::Entry nameEntry{};
    nameEntry.set_placeholder_text("Enter component name");
    nameEntry.set_hexpand(true);
    grid.attach(nameLabel, 0, 1);
    grid.attach(nameEntry, 1, 1);

    // Type dropdown (FC-9)
    Gtk::Label typeLabel{"Type:"};
    Gtk::ComboBoxText typeDropdown;
    typeDropdown.append("Type A");
    typeDropdown.append("Type B");
    typeDropdown.set_active(0);
    grid.attach(typeLabel, 0, 2);
    grid.attach(typeDropdown, 1, 2);

    // Order (FC-10)
    Gtk::Label orderLabel{"Order:"};
    Gtk::Entry orderEntry{};
    orderEntry.set_input_purpose(Gtk::InputPurpose::DIGITS);
    grid.attach(orderLabel, 0, 3);
    grid.attach(orderEntry, 1, 3);

    // Max and Min values (FC-14, FC-15)
    Gtk::Label maxLabel{"Max:"};
    Gtk::Label minLabel{"Min:"};
    Gtk::Entry maxEntry{};
    Gtk::Entry minEntry{};
    maxEntry.set_placeholder_text("Enter max value");
    minEntry.set_placeholder_text("Enter min value");
    grid.attach(maxLabel, 0, 4);
    grid.attach(maxEntry, 1, 4);
    grid.attach(minLabel, 0, 5);
    grid.attach(minEntry, 1, 5);

    // OK and Cancel buttons (FC-18, FC-19)
    Gtk::Button okButton{"OK"};
    Gtk::Button cancelButton{"Cancel"};
    grid.attach(okButton, 0, 6);
    grid.attach(cancelButton, 1, 6);

    // Attach the tab
    m_noteBook.append_page(container, "Filter");
}

void FilterComponentWindow::HandleRadioSelection() {
    // Handle the selection logic for FC-16 and FC-17
}

void FilterComponentWindow::SaveInfo() {
    // Logic to save user inputs
}

};
