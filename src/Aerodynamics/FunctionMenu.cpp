#include "MenuPanel.hpp"

FunctionMenu::FunctionMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->function = std::dynamic_pointer_cast<Function>(node);
    this->setHeader("Function or Operator");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);
}