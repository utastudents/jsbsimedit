#include "DeadbandComponentWindow.hpp"

namespace DragDrop {

DeadbandComponentWindow::DeadbandComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                                                 std::shared_ptr<std::set<std::string>> setOfNames)
    : ComponentWindowCommon(comp, setOfNames) {
    CreateCommonTab();
    CreateDeadbandTab();
}

void DeadbandComponentWindow::CreateDeadbandTab() {
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
    Gtk::Label title{"Deadband Component"};
    grid.attach(title, 0, 0, 2);

    // Name input
    Gtk::Label nameLabel{"Name:"};
    Gtk::Entry nameEntry{};
    nameEntry.set_placeholder_text("Enter component name");
    nameEntry.set_hexpand(true);
    grid.attach(nameLabel, 0, 1);
    grid.attach(nameEntry, 1, 1);

    // Width and Gain
    Gtk::Label widthLabel{"Width:"};
    Gtk::Label gainLabel{"Gain:"};
    Gtk::Entry widthEntry{};
    Gtk::Entry gainEntry{};
    grid.attach(widthLabel, 0, 2);
    grid.attach(widthEntry, 1, 2);
    grid.attach(gainLabel, 0, 3);
    grid.attach(gainEntry, 1, 3);

    // OK and Cancel buttons
    Gtk::Button okButton{"OK"};
    Gtk::Button cancelButton{"Cancel"};
    grid.attach(okButton, 0, 4);
    grid.attach(cancelButton, 1, 4);

    m_noteBook.append_page(container, "Deadband");
}

void DeadbandComponentWindow::HandleRadioSelection() {
    // Handle the selection logic for DB-16 and DB-17
}

void DeadbandComponentWindow::SaveInfo() {
    // Logic to save user inputs
}

};