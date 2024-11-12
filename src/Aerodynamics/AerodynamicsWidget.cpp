#include "AerodynamicsWidget.hpp"

AerodynamicsWidget::AerodynamicsWidget()
: Gtk::Box(Gtk::Orientation::VERTICAL), paned(Gtk::Orientation::HORIZONTAL)
{
    paned.set_start_child(hierarchyPanel);
    paned.set_end_child(menuPanel);
    
    append(paned);
}

