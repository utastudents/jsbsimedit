#include "MenuPanel.hpp"

TableMenu::TableMenu(std::shared_ptr<AerodynamicsNode> node)
{
    this->table = std::dynamic_pointer_cast<Table>(node);
    this->setHeader("Table");
}