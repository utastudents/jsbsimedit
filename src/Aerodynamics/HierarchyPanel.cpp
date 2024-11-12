#include "HierarchyPanel.hpp"

HierarchyPanel::HierarchyPanel() : Gtk::Box(Gtk::Orientation::VERTICAL)
{
    treeStore = Gtk::TreeStore::create(columns);
    treeView.set_model(treeStore);

    treeView.append_column("Aerodynamics", columns.columnName);

    scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolledWindow.set_child(treeView);

    append(scrolledWindow);
    scrolledWindow.set_vexpand(true);

    // Populate tree with sample data
    populateTree();
}

void HierarchyPanel::populateTree()
{
    //TODO: Populate with actual values
    
    treeStore->clear();

    auto rootRow = *(treeStore->append());
    rootRow[columns.columnName] = "Root";

    auto childRow1 = *(treeStore->append(rootRow.children()));
    childRow1[columns.columnName] = "Child 1";

    auto childRow2 = *(treeStore->append(rootRow.children()));
    childRow2[columns.columnName] = "Child 2";

    auto childRow3 = *(treeStore->append(rootRow.children()));
    childRow3[columns.columnName] = "Child 3";

    auto subChildRow1 = *(treeStore->append(childRow1.children()));
    subChildRow1[columns.columnName] = "Subchild 1";

    auto subChildRow2 = *(treeStore->append(childRow2.children()));
    subChildRow2[columns.columnName] = "Subchild 2";
}

void HierarchyPanel::changeMenu()
{
}
