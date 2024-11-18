#include "MenuPanel.hpp"

MenuPanel::MenuPanel() : Gtk::Box(Gtk::Orientation::VERTICAL)
{
    name.set_text("example menu");
    append(name);
}

void MenuPanel::setName(std::string name)
{
    this->name.set_text(name);
}
