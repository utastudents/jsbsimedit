#include "MenuPanel.hpp"

MenuPanel::MenuPanel() : Gtk::Box(Gtk::Orientation::VERTICAL)
{
    name.set_text("example menu");
    append(name);
}

