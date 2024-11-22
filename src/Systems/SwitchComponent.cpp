#include "SwitchComponent.hpp"

namespace DragDrop {

    SwitchComponentWindow::SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp,
                                                 std::shared_ptr<std::set<std::string>> setOfNames)
            : ComponentWindowCommon(comp, setOfNames) {
        CreateCommonTab();
        CreateSwitchTab();
    }

    void SwitchComponentWindow::CreateSwitchTab() {
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
        Gtk::Label title{"Switch Component"};
        grid.attach(title, 0, 0, 2);

        // Name input
        Gtk::Label nameLabel{"Name:"};
        Gtk::Entry nameEntry{};
        nameEntry.set_placeholder_text("Enter component name");
        nameEntry.set_hexpand(true);
        grid.attach(nameLabel, 0, 1);
        grid.attach(nameEntry, 1, 1);

        // Add & Remove Buttons
        Gtk::Button addButton{"Add"};
        Gtk::Button removeButton{"Remove"};
        grid.attach(addButton, 0, 2);
        grid.attach(removeButton, 1, 2);

        // OK and Cancel buttons
        Gtk::Button okButton{"OK"};
        Gtk::Button cancelButton{"Cancel"};
        grid.attach(okButton, 0, 3);
        grid.attach(cancelButton, 1, 3);

        m_noteBook.append_page(container, "Switch");
    }

    void SwitchComponentWindow::SaveInfo() {
        // Logic to save user inputs
    }

};
