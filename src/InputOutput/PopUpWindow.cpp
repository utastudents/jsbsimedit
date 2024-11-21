#include "PopUpWindow.hpp"

PopUpWindow::PopUpWindow() {
    set_title("Properties");
    set_default_size(800, 600);

    // Set up the grid layout
    gridLayout.set_row_spacing(50);
    gridLayout.set_column_spacing(50);
    gridLayout.set_margin(10);
    set_child(gridLayout);

    // Create the TreeView with scrollbars
    auto listStore = Gtk::ListStore::create(propertyColumns);
    propertyTreeView.set_model(listStore);
    
    propertyTreeView.append_column("No.", propertyColumns.index);
    propertyTreeView.append_column("Property Name", propertyColumns.propertyName);
    propertyTreeView.append_column("Description", propertyColumns.description);
    propertyTreeView.append_column("Unit", propertyColumns.unit);
    propertyTreeView.append_column("Access", propertyColumns.access);
    propertyTreeView.append_column("Comments", propertyColumns.comments);

    scrolledWindow.set_child(propertyTreeView);
    scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);

    // Add widgets to the grid
    gridLayout.attach(scrolledWindow, 0, 0, 10, 6); // TreeView spans 10 columns and 6 rows

    // Filter label and text box

    /*Gtk::Label filterLabel{"Filter Level"};
    gridLayout.attach(filterLabel, 0, 6, 2, 1); // Row 6, spans 2 columns
    */
    gridLayout.attach(filterTextBox, 2, 6, 6, 1); // Row 6, spans 6 columns


    // Buttons
    Gtk::Button filterButton{"Filter"}; // Filter Button
    gridLayout.attach(filterButton, 0, 6, 2, 1);    // Row 7, 2 columns wide
    filterButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onFilterButtonClicked));
    
    Gtk::Button showAllButton{"Show All"}; //Show All Button
    gridLayout.attach(showAllButton, 2, 7, 2, 1);  // Row 7, next to filterButton
    showAllButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onShowAllButtonClicked));
   
}


PopUpWindow::~PopUpWindow() {}

void PopUpWindow::onFilterButtonClicked() {
    applyFilter();
}

void PopUpWindow::onShowAllButtonClicked() {
    listStore->clear();
    // Logic to reload the properties list
}

void PopUpWindow::onOkButtonClicked() {
    hide();
}

void PopUpWindow::onCancelButtonClicked() {
    hide();
}

void PopUpWindow::applyFilter() {
    Glib::ustring filterText = filterTextBox.get_text().lowercase();
    listStore->clear();

}
