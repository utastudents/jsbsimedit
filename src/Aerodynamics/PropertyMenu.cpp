#include "MenuPanel.hpp"

PropertyMenu::PropertyMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->property = std::dynamic_pointer_cast<AeroProperty>(node);
    this->setHeader("Properties");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);
}