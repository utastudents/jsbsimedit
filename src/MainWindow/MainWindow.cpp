#include "MainWindow.h"
#include <gtkmm.h>
#include <iostream>
#if 0
// Function to create a new tab in the notebook
void create_tab(Gtk::Notebook& notebook, const Glib::ustring& tab_name, Gtk::Widget& content) {
    // Create a label for the tab
    Gtk::Label* tab_label = Gtk::manage(new Gtk::Label(tab_name));

    // Add the content to the notebook with the tab label
    notebook.append_page(content, *tab_label);

    // Make sure all widgets inside content are visible
    content.show_all();
}

// Function to create an example content box for JSBSim XML data
Gtk::Box* create_example_jsbsim_box() {
    // Create a vertical box to hold the widgets
    Gtk::Box* content_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    // Create a frame to group related widgets
    Gtk::Frame* frame = Gtk::manage(new Gtk::Frame("JSBSim XML Data"));

    // Create a grid to arrange labels and entries
    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
    grid->set_row_spacing(5);
    grid->set_column_spacing(10);

    // Placeholder labels and entries for XML data fields
    Gtk::Label* label1 = Gtk::manage(new Gtk::Label("Aircraft Name:"));
    Gtk::Entry* entry1 = Gtk::manage(new Gtk::Entry());
    entry1->set_placeholder_text("Enter aircraft name");

    Gtk::Label* label2 = Gtk::manage(new Gtk::Label("Engine Type:"));
    Gtk::Entry* entry2 = Gtk::manage(new Gtk::Entry());
    entry2->set_placeholder_text("Enter engine type");

    Gtk::Label* label3 = Gtk::manage(new Gtk::Label("Wingspan:"));
    Gtk::Entry* entry3 = Gtk::manage(new Gtk::Entry());
    entry3->set_placeholder_text("Enter wingspan");

    // Add labels and entries to the grid
    grid->attach(*label1, 0, 0, 1, 1);
    grid->attach(*entry1, 1, 0, 1, 1);

    grid->attach(*label2, 0, 1, 1, 1);
    grid->attach(*entry2, 1, 1, 1, 1);

    grid->attach(*label3, 0, 2, 1, 1);
    grid->attach(*entry3, 1, 2, 1, 1);

    // Add the grid to the frame
    frame->add(*grid);

    // Create a button to simulate an action (e.g., save data)
    Gtk::Button* save_button = Gtk::manage(new Gtk::Button("Save Data"));

    // Pack the frame and button into the content box
    content_box->pack_start(*frame, Gtk::PACK_SHRINK);
    content_box->pack_start(*save_button, Gtk::PACK_SHRINK);

    // Show all widgets in the content box
    content_box->show_all();

    return content_box;
}
// Main function to run the application
int main(int argc, char* argv[]) {
    // Create the GTK application
    auto app = Gtk::Application::create(argc, argv, "com.example.notebookapp");

    // Create an instance of the main window
    MainWindow window;

    // Run the application
    return app->run(window);
}
#endif
