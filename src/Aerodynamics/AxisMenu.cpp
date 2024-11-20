#include "MenuPanel.hpp"

AxisMenu::AxisMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->axis = std::dynamic_pointer_cast<Axis>(node);
    this->setHeader("Axis");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    auto dropdown = Gtk::make_managed<Gtk::DropDown>();
    auto string_list = Gtk::StringList::create();
    for (const auto& axisName : Axis::axisNameToString) {
        string_list->append(axisName.second);
    }
    dropdown->set_model(string_list);
    grid->attach(*dropdown,0,1);
}