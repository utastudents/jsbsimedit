#include "MenuPanel.hpp"

ValueMenu::ValueMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->value = std::dynamic_pointer_cast<Value>(node);
    this->setHeader("Value");

    // Attach UI elements to this grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    inputLabel = Gtk::make_managed<Gtk::Label>("Value");
    grid->attach(*inputLabel,0,0);
    inputEntry = Gtk::make_managed<Gtk::Entry>();
    grid->attach(*inputEntry, 1,0);
    inputEntry->set_text(std::to_string(value->getInput()));
    inputEntry->property_text().signal_changed().connect(sigc::mem_fun(*this,&ValueMenu::on_text_changed));

}
// is to update text
void ValueMenu::on_text_changed(){
    value->setInput(std::stod(inputEntry->get_text()));
    update_signal.emit();
}