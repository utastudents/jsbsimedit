#include "MenuPanel.hpp"
#include <gtkmm.h>
#include <regex>

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
    //defines input and label and entry 
    inputLabel = Gtk::make_managed<Gtk::Label>("Value:");
    inputLabel->set_halign(Gtk::Align::START);
    grid->attach(*inputLabel,0,0);
    inputEntry = Gtk::make_managed<Gtk::Entry>();
    grid->attach(*inputEntry, 1,0);
    inputEntry->set_text(std::to_string(value->getInput()));
    inputEntry->set_tooltip_text("Enter a numerical value");
     
    // defines label 
    saveButton = Gtk::make_managed<Gtk::Button>();
    saveButton->set_label("Save");
    saveButton->set_tooltip_text("Save changes to this value");
    saveButton->signal_clicked().connect(sigc::mem_fun(*this,&ValueMenu::on_save_clicked));
    grid->attach(*saveButton,1,1);
    
}
// is now only allowing #'s and no letters
void ValueMenu::on_save_clicked(){
    try {
        double value = std::stod(inputEntry->get_text());
        this->value->setInput(value);
        update_signal.emit();

    }catch (...) {
        inputEntry->set_tooltip_text("Please enter only valid numbers.");
        inputEntry->set_text("");
    } 
}

