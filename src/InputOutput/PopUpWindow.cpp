#include "PopUpWindow.hpp"

PopUpWindow::PopUpWindow()
    : filterButton("Filter"),
      showAllButton("Show All"),
      okButton("OK"),
      cancelButton("Cancel"),
      m_VBox(Gtk::Orientation::VERTICAL, 10) {

    set_title("Properties");
    set_default_size(800, 600);

    // Main vertical box container
    set_child(m_VBox);
    m_VBox.set_margin(10);

    // Scrolled window for the property list
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    // Set up the TreeView
    listStore = Gtk::ListStore::create(propertyColumns);
    propertyTreeView.set_model(listStore);

    propertyTreeView.append_column("No.", propertyColumns.index);
    propertyTreeView.append_column("Property Name", propertyColumns.propertyName);
    propertyTreeView.append_column("Description", propertyColumns.description);
    propertyTreeView.append_column("Unit", propertyColumns.unit);
    propertyTreeView.append_column("Access", propertyColumns.access);
    propertyTreeView.append_column("Comments", propertyColumns.comments);

    // Add the TreeView to the ScrolledWindow
    m_ScrolledWindow.set_child(propertyTreeView);

    // Create a Frame for properties
    auto propertiesFrame = Gtk::make_managed<Gtk::Frame>("");
    propertiesFrame->set_child(m_ScrolledWindow);
    m_VBox.append(*propertiesFrame);

    // Create a Grid for filter buttons and show all button
    auto filterGrid = Gtk::make_managed<Gtk::Grid>();
    filterGrid->set_row_spacing(10);  
    filterGrid->set_column_spacing(10); 


    // Set the expand property for the widgets in the grid
    filterTextBox.set_hexpand(true);  
    filterButton.set_hexpand(false);  
    showAllButton.set_hexpand(false);  



    // Place the filter text box and buttons in the grid
    filterGrid->attach(filterTextBox, 1, 0, 7, 1);  
    filterGrid->attach(filterButton, 0, 0, 1, 1);   
    filterGrid->attach(showAllButton, 8, 0, 1, 1);  


    // Add filter grid to the vertical box (m_VBox)
    m_VBox.append(*filterGrid);

    // Create a Grid for OK and Cancel buttons
    auto buttonGrid = Gtk::make_managed<Gtk::Grid>();
    buttonGrid->set_row_spacing(10);   
    buttonGrid->set_column_spacing(10); 

    // Add OK and Cancel buttons
    buttonGrid->attach(okButton, 0, 0, 1, 1);  
    buttonGrid->attach(cancelButton, 1, 0, 1, 1);     

    // Make both buttons expand horizontally to take equal space
    okButton.set_hexpand(true);  
    cancelButton.set_hexpand(true);  

    // Add the button grid to the vertical box (m_VBox)
    m_VBox.append(*buttonGrid);

    // Signal connections for buttons
    filterButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onFilterButtonClicked));
    showAllButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onShowAllButtonClicked));
    okButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onOkButtonClicked));
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &PopUpWindow::onCancelButtonClicked));
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
    // Filter logic here
}
