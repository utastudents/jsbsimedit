#include "MenuPanel.hpp"

AxisMenu::AxisMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->axis = std::dynamic_pointer_cast<Axis>(node);
    this->setHeader("Axis");

    // Attach UI elements to this grid
    grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    // Populate the dropdown menu with axis names
    nameDropdown = Gtk::make_managed<Gtk::DropDown>();
    name_list = Gtk::StringList::create();
    for (const auto& axisName : Axis::axisNameToString) {
        name_list->append(axisName.second);
    }
    nameDropdown->set_model(name_list);
    nameDropdownLabel = Gtk::make_managed<Gtk::Label>("Axis Name");
    grid->attach(*nameDropdownLabel,0,0);
    grid->attach(*nameDropdown,1,0);

    // Set the selected item to the correct axis name
    int index = 0;
    for (const auto& axisName : Axis::axisNameToString) {
        if (axisName.second == Axis::axisNameToString[axis->getName()]) {
            nameDropdown->set_selected(index);
            break;
        }
        index++;
    }

    // Connect the dropdown selection signal to a function
    nameDropdown->property_selected().signal_changed().connect(sigc::mem_fun(*this, &AxisMenu::on_name_dropdown_selected));

    // Populate the dropdown menu with unit names
    unitDropdown = Gtk::make_managed<Gtk::DropDown>();
    unit_list = Gtk::StringList::create();
    for (const auto& unitName : Axis::unitNameToString) {
        unit_list->append(unitName.second);
    }
    unitDropdown->set_model(unit_list);
    unitDropdownLabel = Gtk::make_managed<Gtk::Label>("Unit");
    grid->attach(*unitDropdownLabel,0,1);
    grid->attach(*unitDropdown,1,1);

    // Set the selected item to the correct axis name
    index = 0;
    for (const auto& unitName : Axis::unitNameToString) {
        if (unitName.second == Axis::unitNameToString[axis->getUnit()]) {
            unitDropdown->set_selected(index);
            break;
        }
        index++;
    }

    // Connect the dropdown selection signal to a function
    unitDropdown->property_selected().signal_changed().connect(sigc::mem_fun(*this, &AxisMenu::on_unit_dropdown_selected));
}

void AxisMenu::on_name_dropdown_selected() {
    std::string newName = name_list->get_string(nameDropdown->get_selected());
    axis->setName(Axis::stringToAxisName[newName]);
    update_signal.emit();
}

void AxisMenu::on_unit_dropdown_selected() {
    std::string newUnit = unit_list->get_string(unitDropdown->get_selected());
    axis->setUnit(Axis::stringToUnitName[newUnit]);
    update_signal.emit();
}