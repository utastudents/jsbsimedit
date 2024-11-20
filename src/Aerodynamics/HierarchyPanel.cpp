#include "HierarchyPanel.hpp"

// Constructor: Initializes the HierarchyPanel, sets up the tree view and window properties
HierarchyPanel::HierarchyPanel() : Gtk::ScrolledWindow()
{
    // Set up the tree view and connect a signal
    treeView.append_column("Aerodynamics", columns.columnName);
    treeView.set_headers_visible(false);
    treeView.set_activate_on_single_click(true);
    treeView.signal_row_activated().connect(sigc::mem_fun(*this, &HierarchyPanel::on_row_activated));

    // Configuring this window
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);  
    set_child(treeView);
    set_vexpand(true);
}

// Emits a signal when a row is activated
void HierarchyPanel::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    // Get the row from the TreeModel using the path
    Gtk::TreeModel::iterator iter = treeStore->get_iter(path);
    if (iter) {
        std::shared_ptr<AerodynamicsNode> node = (*iter)[columns.node];

        row_activated_signal.emit(node);
    }
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
