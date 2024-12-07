#include "SwitchComponentWindow.hpp"
#include <gtkmm/togglebutton.h> // Correct Button

namespace DragDrop {

SwitchComponentWindow::SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                                             std::shared_ptr<std::set<std::string>> setOfNames)
    : ComponentWindowCommon(comp, setOfNames) {
    CreateCommonTab();
    SwitchBasic();
    SwitchInput();
    SwitchOutput();
}

void SwitchComponentWindow::SwitchBasic() {
    Gtk::Grid grid{};
    grid.set_margin_top(75);
    grid.set_margin_start(50);

    Gtk::Label clippableLabel{"Clippable"};
    Gtk::CheckButton clippableCheckbox;

    // Use the public getter method instead of directly accessing m_component
    auto component = GetComponent();
    auto switchComp = dynamic_cast<SwitchComponent*>(component.get());
    if (switchComp) {
        clippableCheckbox.set_active(switchComp->IsClipperEnabled);
    }

    Gtk::Label maxLabel{"Max:"};
    Gtk::Entry maxEntry;
    Gtk::Label minLabel{"Min:"};
    Gtk::Entry minEntry;

    grid.attach(clippableLabel, 0, 0);
    grid.attach(clippableCheckbox, 1, 0);
    grid.attach(maxLabel, 0, 1);
    grid.attach(maxEntry, 1, 1);
    grid.attach(minLabel, 0, 2);
    grid.attach(minEntry, 1, 2);

    m_noteBook.append_page(grid, "Basic");
}

void SwitchComponentWindow::SwitchInput() {
    Gtk::Grid grid{};
    Gtk::Label setLabel{"Set:"};

    // Implement Toggle Buttons for now
    Gtk::ToggleButton positiveBtn("Positive");
    Gtk::ToggleButton negativeBtn("Negative");

    // Logic for Add/Remove
    Gtk::Button addButton{"Add"};
    Gtk::Button removeButton{"Remove"};

    grid.attach(setLabel, 0, 0);
    grid.attach(positiveBtn, 1, 0);
    grid.attach(negativeBtn, 2, 0);
    grid.attach(addButton, 0, 1);
    grid.attach(removeButton, 1, 1);

    m_noteBook.append_page(grid, "Input");
}

void SwitchComponentWindow::SwitchOutput() {
    Gtk::Grid grid{};
    Gtk::Label outputLabel{"Outputs:"};
    Gtk::ListBox outputBox{};
    Gtk::Button applyButton{"Apply"};

    grid.attach(outputLabel, 0, 0);
    grid.attach(outputBox, 1, 0);
    grid.attach(applyButton, 1, 1);

    m_noteBook.append_page(grid, "Tree");
}

void SwitchComponentWindow::SaveInfo() {
    // Collect info from GUI for saving XML configurations
}

}