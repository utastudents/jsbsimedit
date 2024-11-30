#include "MenuPanel.hpp"

TableMenu::TableMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->table = std::dynamic_pointer_cast<Table>(node);
    this->setHeader("Table");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);
}