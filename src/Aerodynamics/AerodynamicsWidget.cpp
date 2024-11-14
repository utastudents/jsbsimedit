#include "AerodynamicsWidget.hpp"

AerodynamicsWidget::AerodynamicsWidget()
: Gtk::Paned(Gtk::Orientation::HORIZONTAL)
{
    set_start_child(hierarchyPanel);
    set_end_child(menuPanel);
}

