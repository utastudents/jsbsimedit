#include "MenuPanel.hpp"

ValueMenu::ValueMenu(std::shared_ptr<AerodynamicsNode> node)
{
    this->value = std::dynamic_pointer_cast<Value>(node);
    this->setHeader("Value");
}
