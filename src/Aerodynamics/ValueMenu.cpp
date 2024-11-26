#include "MenuPanel.hpp"

ValueMenu::ValueMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->value = std::dynamic_pointer_cast<Value>(node);
    this->setHeader("Value");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);
}
