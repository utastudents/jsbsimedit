#include "MenuPanel.hpp"

AxisMenu::AxisMenu(std::shared_ptr<AerodynamicsNode> node)
{
    this->axis = std::dynamic_pointer_cast<Axis>(node);
    this->setHeader("Axis");

    auto dropdown = Gtk::make_managed<Gtk::DropDown>();
    auto string_list = Gtk::StringList::create();
    for (const auto& axisName : Axis::axisNameToString) {
        string_list->append(axisName.second);
    }
    dropdown->set_model(string_list);
    attach(*dropdown,0,1);
}