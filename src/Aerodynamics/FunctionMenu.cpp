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

    //creates Name Field
    int index = 0;
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name:");
    nameLabel->set_halign(Gtk::Align::START);
    grid->attach(*nameLabel, 0, index, 1, 1);

    nameEntry = Gtk::make_managed<Gtk::Entry>();
    nameEntry->set_text(function ? function->getName() : "");
    grid->attach(*nameEntry, 1, index++, 1, 1);

    //creates Description Field
    auto descriptionLabel = Gtk::make_managed<Gtk::Label>("Description:");
    descriptionLabel->set_halign(Gtk::Align::START);
    grid->attach(*descriptionLabel, 0, index, 1, 1);

    descriptionEntry = Gtk::make_managed<Gtk::Entry>();
    descriptionEntry->set_text(function ? function->getDescription() : "");
    grid->attach(*descriptionEntry, 1, index++, 1, 1);


}
