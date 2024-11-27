#include "MenuPanel.hpp"
#include "inc/XML_api.hpp"
#include "NewPropertyPopup.hpp"

PropertyMenu::PropertyMenu(std::shared_ptr<AerodynamicsNode> node)
    : filterButton("Filter"),
      showAllButton("Show All"),
      okButton("OK"),
      cancelButton("Cancel"),
      m_VBox(Gtk::Orientation::VERTICAL, 10),
      currentPlaceholder(Gtk::make_managed<Gtk::Entry>()) 
{
    // Make changes to this object vvv
    this->property = std::dynamic_pointer_cast<AeroProperty>(node);
    this->setHeader("Properties");

    append(m_VBox);

    // Add container for the scrolled window and current label
    auto scrolledContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    
    // Added current label
    auto currentHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    currentLabel.set_text("Current:");
    currentLabel.set_margin(5);
    currentHBox->append(currentLabel);
     
    // Added box to show selected property
    currentPlaceholder->set_text("");
    currentPlaceholder->set_editable(false);
    currentPlaceholder->set_width_chars(20);
    currentHBox->append(*currentPlaceholder);
    
    scrolledContainer->append(*currentHBox);

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

    // Add the scrolled window to the container
    scrolledContainer->append(m_ScrolledWindow);

    // Add the container to the main VBox
    m_VBox.append(*scrolledContainer);

    // Connect the selection signal to update the current label
    auto selection = propertyTreeView.get_selection();
    selection->signal_changed().connect(sigc::mem_fun(*this, &PropertyMenu::onPropertySelected));

    // Open and load the XML document
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../properties.xml"});
    JSBEdit::XMLNode propertyNode = doc.GetNodes("/properties")[0];
    std::vector<JSBEdit::XMLNode> propertyNodes = propertyNode.GetChildren();

    // Populate with property names
    std::vector<std::string> propertyNames;
    for (auto i : propertyNodes) {
        auto text = i.GetText();
        propertyNames.push_back(text.substr(1));
    }

    // Populate the list store
    // TODO: check for information fo other columns
    for (size_t i = 0; i < propertyNames.size(); ++i) {
        auto row = *(listStore->append());
        row[propertyColumns.index] = i + 1;                   // Serial numbers starting from 1
        row[propertyColumns.propertyName] = propertyNames[i];
    }

    // Select and scroll to the currently selected property if present
    bool containsProperty = false;
    for (const auto& i : listStore->children()) {
        Glib::ustring name = i[propertyColumns.propertyName];
        if (name.raw() == property->getName()) {
            selection->select(i.get_iter());
            propertyTreeView.scroll_to_row(listStore->get_path(i.get_iter()));
            containsProperty = true;
            break;
        }
    }

    // If we dont have the property in our XML file we open this dialog window
    if(!containsProperty) {
        NewPropertyPopup* popup = Gtk::make_managed<NewPropertyPopup>(property->getName());
        popup->show();
        popup->set_modal(true);
        popup->addProperty.connect(sigc::mem_fun(*this, &PropertyMenu::addProperty));   // If the user confirms we go ahead and add the property
    }

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
    filterButton.signal_clicked().connect(sigc::mem_fun(*this, &PropertyMenu::onFilterButtonClicked));
    showAllButton.signal_clicked().connect(sigc::mem_fun(*this, &PropertyMenu::onShowAllButtonClicked));
    okButton.signal_clicked().connect(sigc::mem_fun(*this, &PropertyMenu::onOkButtonClicked));
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &PropertyMenu::onCancelButtonClicked));
}

void PropertyMenu::onFilterButtonClicked() {
    applyFilter();
}

void PropertyMenu::onShowAllButtonClicked() {
    listStore->clear();
    // Logic to reload the properties list
}

void PropertyMenu::onOkButtonClicked() {
    hide();
}

void PropertyMenu::onCancelButtonClicked() {
    hide();
}

void PropertyMenu::applyFilter() {
    Glib::ustring filterText = filterTextBox.get_text().lowercase();
    listStore->clear();
    // Filter logic here
}

// Function to handle property selection
void PropertyMenu::onPropertySelected() {
    auto selection = propertyTreeView.get_selection();
    if (auto iter = selection->get_selected()) {
        auto row = *iter;
        Glib::ustring propertyName = row[propertyColumns.propertyName];
        currentPlaceholder->set_text(propertyName); // Update placeholder with selected property
    }
}

// Function to add the unknown property into the tree view as well as adding it to properties.xml
void PropertyMenu::addProperty() {
    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../properties.xml"});
    auto propertyNode = doc.GetNodes("/properties")[0];
    JSBEdit::XMLNode newProperty(doc);
    newProperty.SetName("property");
    newProperty.SetText("/" + property->getName());
    propertyNode.AddChild(newProperty);
    doc.SaveToFile({"../../../properties.xml"});

    auto row = *(listStore->append());
    row[propertyColumns.index] = listStore->children().size();
    row[propertyColumns.propertyName] = property->getName();
    auto selection = propertyTreeView.get_selection();
    selection->select(row.get_iter());
    propertyTreeView.scroll_to_row(listStore->get_path(row.get_iter()));
}