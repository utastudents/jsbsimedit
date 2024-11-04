#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <iostream>

// Main application window class
class MainWindow : public Gtk::Window {
public:
    MainWindow() {
        // Set the window title and default size
        set_title("Main Window with Notebook");
        set_default_size(800, 600);

        // Add the notebook to the window
        add(main_notebook);

        // Show the notebook
        main_notebook.show();

        // Example: Create a new tab with JSBSim placeholder content
        Gtk::Box* jsbsim_content = create_example_jsbsim_box();

        // Create a new tab with the JSBSim content
        create_tab(main_notebook, "JSBSim Data Tab", *jsbsim_content);
    }
    Gtk::Box* create_example_jsbsim_box();
    void create_tab(Gtk::Notebook& notebook, const Glib::ustring& tab_name, Gtk::Widget& content);
private:
    Gtk::Notebook main_notebook; // The main notebook widget
};

#endif
