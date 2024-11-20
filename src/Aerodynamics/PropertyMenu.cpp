#include "MenuPanel.hpp"

PropertyMenu::PropertyMenu(std::shared_ptr<AerodynamicsNode> node)
{
    this->property = std::dynamic_pointer_cast<AeroProperty>(node);
    this->setHeader("Properties");
}