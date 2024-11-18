#include "HierarchyPanel.hpp"

// Constructor: Initializes the HierarchyPanel, sets up the tree view and window properties
HierarchyPanel::HierarchyPanel() : Gtk::ScrolledWindow()
{
    // Set up the tree view column for node names
    treeView.append_column("Aerodynamics", columns.columnName);
    treeView.set_headers_visible(false);

    // Configuring this window
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);  
    set_child(treeView);
    set_vexpand(true);
}

// Populates the tree view with the provided TreeStore model
void HierarchyPanel::populateTree(Glib::RefPtr<Gtk::TreeStore> treeStore)
{
    this->treeStore = treeStore;
    treeView.set_model(this->treeStore);
}

// Getter for the ModelColumns definition
const HierarchyPanel::ModelColumns& HierarchyPanel::getColumns()
{
    return columns;
}
