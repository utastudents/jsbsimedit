#include "HierarchyPanel.hpp"

// Constructor: Initializes the HierarchyPanel, sets up the tree view and window properties
HierarchyPanel::HierarchyPanel() : Gtk::ScrolledWindow()
{   

    Gtk::TreeViewColumn* column = Gtk::manage(new Gtk::TreeViewColumn());
    column->set_title("Hierarchy");
    
    // Create the cell renderers for the icon and the text
    Gtk::CellRendererPixbuf* renderer_pixbuf = Gtk::manage(new Gtk::CellRendererPixbuf());
    Gtk::CellRendererText* renderer_text = Gtk::manage(new Gtk::CellRendererText());
    
    // Add the renderers to the column
    column->pack_start(*renderer_pixbuf, false);
    column->pack_start(*renderer_text, true);

    // Bind the columns to the model
    column->add_attribute(renderer_pixbuf->property_pixbuf(), columns.icon);
    column->add_attribute(renderer_text->property_text(), columns.columnName);
    
    // Set column properties
    column->set_expand(true);

    // Add column to TreeView
    treeView.append_column(*column);

    treeView.set_headers_visible(false);
    treeView.set_tooltip_text("Select a row to open the corresponding menu");
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
    column->get_title();
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
