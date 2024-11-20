#include "MenuPanel.hpp"

FunctionMenu::FunctionMenu(std::shared_ptr<AerodynamicsNode> node)
{
    this->function = std::dynamic_pointer_cast<Function>(node);
    this->setHeader("Function or Operator");
}