#include "PopUpWindow.hpp"
#include "inc/XML_api.hpp"
#include <fstream>

PopUpWindow::PopUpWindow()
    : filterButton("Filter"),
      showAllButton("Show All"),
      okButton("OK"),
      cancelButton("Cancel"),
      m_VBox(Gtk::Orientation::VERTICAL, 10),
      currentPlaceholder(Gtk::make_managed<Gtk::Entry>()) { // Initialize currentPlaceholder

    set_title("Properties");
    set_default_size(800, 600);

    // Main vertical box container
    set_child(m_VBox);
    m_VBox.set_margin(10);

    // Add container for the scrolled window and current label
    auto scrolledContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    
    // Added current label
    auto currentHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    currentLabel.set_text("Current:");
    currentLabel.set_margin(5);
    showLabel.set_text("Show: 0");
    hideLabel.set_text("Hide: 0");
    showLabel.set_margin(5);
    hideLabel.set_margin(5);
    currentHBox->append(currentLabel);
    
    // Added box to show selected property
    currentPlaceholder->set_text("");
    currentPlaceholder->set_editable(false);
    currentPlaceholder->set_width_chars(20);
    currentHBox->append(*currentPlaceholder);
    currentHBox->append(showLabel);
    currentHBox->append(hideLabel);
    
    scrolledContainer->append(*currentHBox);

    // Scrolled window for the property list
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    // Set up the TreeView
    listStore = Gtk::ListStore::create(propertyColumns);
    propertyTreeView.set_model(listStore);

    // Append columns and set their minimum widths separately
    auto col_index = propertyTreeView.append_column("No.", propertyColumns.index);
    auto col_name = propertyTreeView.append_column("Property Name", propertyColumns.propertyName);
    auto col_description = propertyTreeView.append_column("Description", propertyColumns.description);
    auto col_unit = propertyTreeView.append_column("Unit", propertyColumns.unit);
    auto col_access = propertyTreeView.append_column("Access", propertyColumns.access);
    auto col_comments = propertyTreeView.append_column("Comments", propertyColumns.comments);

    // Set minimum widths for each column
    propertyTreeView.get_column(col_index - 1)->set_min_width(50);
    propertyTreeView.get_column(col_name - 1)->set_min_width(200);
    propertyTreeView.get_column(col_description - 1)->set_min_width(150);
    propertyTreeView.get_column(col_unit - 1)->set_min_width(100);
    propertyTreeView.get_column(col_access - 1)->set_min_width(100);
    propertyTreeView.get_column(col_comments - 1)->set_min_width(200);

    // Add the TreeView to the ScrolledWindow
    m_ScrolledWindow.set_child(propertyTreeView);

    // Add the scrolled window to the container
    scrolledContainer->append(m_ScrolledWindow);

    // Add the container to the main VBox
    m_VBox.append(*scrolledContainer);

    // Connect the selection signal to update the current label
    auto selection = propertyTreeView.get_selection();
    selection->signal_changed().connect(sigc::mem_fun(*this, &PopUpWindow::onPropertySelected));

    //This xmlFile method is hardcode, need to find another way to use xmlptr()
    JSBEdit::XMLDoc xmlFile;
    xmlFile.LoadFileAndParse({"../../../properties.xml"});

    auto parentNode = xmlFile.GetNode("/properties");
    auto properties = parentNode.GetChildren();

    int i = 1; // Row ID
    for (const auto& property : properties) {
        auto mutableProperty = const_cast<JSBEdit::XMLNode&>(property);

        if (mutableProperty.GetName() == "property") { // Check if the node is a <property>
        std::string propertyText = mutableProperty.GetText();

        // Remove first '/' from view
        if (!propertyText.empty() && propertyText[0] == '/') {
            propertyText = propertyText.substr(1);
        }
            auto tableRow = *(listStore->append());
            tableRow[propertyColumns.propertyName] = propertyText;
            tableRow[propertyColumns.index] = i++;
        }
    }

    // Create a Grid for filter buttons and show all button
    auto filterGrid = Gtk::make_managed<Gtk::Grid>();
    filterGrid->set_row_spacing(10);  
    filterGrid->set_column_spacing(10); 

    filterTextBox.set_hexpand(true);  
    filterButton.set_hexpand(false);  
    showAllButton.set_hexpand(false);  

    filterGrid->attach(filterTextBox, 1, 0, 7, 1);  
    filterGrid->attach(filterButton, 0, 0, 1, 1);   
    filterGrid->attach(showAllButton, 8, 0, 1, 1);  

    m_VBox.append(*filterGrid);

    auto buttonGrid = Gtk::make_managed<Gtk::Grid>();
    buttonGrid->set_row_spacing(10);   
    buttonGrid->set_column_spacing(10); 

    buttonGrid->attach(okButton, 0, 0, 1, 1);  
    buttonGrid->attach(cancelButton, 1, 0, 1, 1);     

    okButton.set_hexpand(true);  
    cancelButton.set_hexpand(true);  

    m_VBox.append(*buttonGrid);

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

// Function to handle property selection
void PopUpWindow::onPropertySelected() {
    auto selection = propertyTreeView.get_selection();
    if (auto iter = selection->get_selected()) {
        auto row = *iter;
        Glib::ustring propertyName = row[propertyColumns.propertyName];
        currentPlaceholder->set_text(propertyName); // Update placeholder with selected property
        selectedProperty = propertyName;           // Store selected property
    }
}

// New method to return the selected property
std::string PopUpWindow::getSelectedProperty() {
    return selectedProperty; // Return the stored property
}

void PopUpWindow::updateShowHideCounts() {
    int showCount = 0;
    int hideCount = 0;

    for (auto& row : listStore->children()) {
        Glib::ustring propertyName = row[propertyColumns.propertyName];
        
        if (propertyName.lowercase().find(filterTextBox.get_text().lowercase()) != std::string::npos) {
            ++showCount;
        } else {
            ++hideCount;
        }
    }

    showLabel.set_text("Show: " + std::to_string(showCount));
    hideLabel.set_text("Hide: " + std::to_string(hideCount));
}

