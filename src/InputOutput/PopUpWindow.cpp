#include "PopUpWindow.hpp"

PopUpWindow::PopUpWindow() {
    set_title("Properties");
    set_default_size(800, 600);

    //Set up the grid layout
    gridLayout.set_row_spacing(50);
    gridLayout.set_column_spacing(50);
    gridLayout.set_margin(10);
    set_child(gridLayout);

    scrolledWindowV.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    set_child(scrolledWindowV); 

    auto listStore = Gtk::ListStore::create(propertyColumns);
    propertyTreeView.set_model(listStore);

    // Add columns to TreeView
    propertyTreeView.append_column("No.", propertyColumns.index);
    propertyTreeView.append_column("Property Name", propertyColumns.propertyName);
    propertyTreeView.append_column("Description", propertyColumns.description);
    propertyTreeView.append_column("Unit", propertyColumns.unit);
    propertyTreeView.append_column("Access", propertyColumns.access);
    propertyTreeView.append_column("Comments", propertyColumns.comments);

    scrolledWindowV.set_child(propertyTreeView); 

    // Set up button signals
    filterButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onFilterButtonClicked));
    showAllButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onShowAllButtonClicked));
    okButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onOkButtonClicked));
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onCancelButtonClicked));
}

PopUpWindow::~PopUpWindow() {} //Destructor

void PopUpWindow::onFilterButtonClicked() {}

void PopUpWindow::onShowAllButtonClicked() {}

void PopUpWindow::onOkButtonClicked() {
    hide(); 
}

void PopUpWindow::onCancelButtonClicked() {
    hide(); 
}

void PopUpWindow::loadPropertiesFromFile(const std::string& fileName) {
    // Load properties from file.
}
