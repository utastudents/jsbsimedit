#pragma once

#include <gtkmm.h>

// A dialog window to determine if the user wants to add an unknown property to properties.xml
class NewPropertyPopup : public Gtk::Window {
public:
    NewPropertyPopup(std::string propertyName);
    using AddProperty = sigc::signal<void()>;
    AddProperty addProperty;
private:
    void on_cancel_button_clicked();
    void on_confirm_button_clicked();
    Gtk::Box* box;
    Gtk::Grid* grid;
    Gtk::Label* dialog;
    Gtk::Button* confirm_button;
    Gtk::Button* cancel_button;
};