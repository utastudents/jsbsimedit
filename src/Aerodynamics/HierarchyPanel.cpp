#include "HierarchyPanel.hpp"

HierarchyPanel::HierarchyPanel() : Gtk::ScrolledWindow()
{
    treeView.append_column("Aerodynamics", columns.columnName);
    treeView.set_headers_visible(false);

    //configure this window
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    set_child(treeView);
    set_vexpand(true);
}

void HierarchyPanel::populateTree(Glib::RefPtr<Gtk::TreeStore> treeStore)
{
    this->treeStore = treeStore;
    treeView.set_model(this->treeStore);
}

void HierarchyPanel::changeMenu()
{
}

const HierarchyPanel::ModelColumns& HierarchyPanel::getColumns()
{
    return columns;
}
