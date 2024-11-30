#include "NewPropertyPopup.hpp"

NewPropertyPopup::NewPropertyPopup(std::string propertyName) {
    set_title("New Property");
    set_default_size(300, 0);

    // Create the box
    box = Gtk::make_managed<Gtk::Box>();
    box->set_orientation(Gtk::Orientation::VERTICAL);
    set_child(*box);

    // Create the dialog text
    dialog = Gtk::make_managed<Gtk::Label>();
    dialog->set_text("The property \"" + propertyName + "\" could not be found. Would you like to add it to the list of properties?");
    dialog->set_wrap(true);
    dialog->set_margin(10);
    dialog->set_halign(Gtk::Align::CENTER);
    box->append(*dialog);


    // Create the grid for the buttons
    grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    grid->set_halign(Gtk::Align::CENTER);
    grid->set_margin(10);
    box->append(*grid);

    // Set up the close button and attach a signal
    cancel_button = Gtk::make_managed<Gtk::Button>();
    cancel_button->set_label("Cancel");
    cancel_button->signal_clicked().connect(sigc::mem_fun(*this, &NewPropertyPopup::on_cancel_button_clicked));
    grid->attach(*cancel_button,0,0);

    // Set up the confirm button and attach a signal
    confirm_button = Gtk::make_managed<Gtk::Button>();
    confirm_button->set_label("Confirm");
    confirm_button->signal_clicked().connect(sigc::mem_fun(*this, &NewPropertyPopup::on_confirm_button_clicked));
    grid->attach(*confirm_button,1,0);
}

// Does not emit a signal to add the property
void NewPropertyPopup::on_cancel_button_clicked() {
    hide();
}

// Emits a signal to add the property
void NewPropertyPopup::on_confirm_button_clicked() {
    addProperty.emit();
    hide();
}