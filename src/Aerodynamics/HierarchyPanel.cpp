#include "HierarchyPanel.hpp"

HierarchyPanel::HierarchyPanel() : Gtk::ScrolledWindow()
{
    //configure this window
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    set_child(treeView);
    set_vexpand(true);

    treeStore = Gtk::TreeStore::create(columns);
    treeView.set_model(treeStore);

    treeView.append_column("Aerodynamics", columns.columnName);

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
    childRow1[columns.columnName] = "Drag due to...";

    auto childRow2 = *(treeStore->append(rootRow.children()));
    childRow2[columns.columnName] = "Lift due to...";

    auto childRow3 = *(treeStore->append(rootRow.children()));
    childRow3[columns.columnName] = "Pitch";

    auto childRow4 = *(treeStore->append(rootRow.children()));
    childRow4[columns.columnName] = "Yaw";

    auto childRow5 = *(treeStore->append(rootRow.children()));
    childRow5[columns.columnName] = "Roll";

    auto subChildRow1 = *(treeStore->append(childRow1.children()));
    subChildRow1[columns.columnName] = "P property 1";

    auto subChildRow2 = *(treeStore->append(childRow2.children()));
    subChildRow2[columns.columnName] = "P property 1";
}

void HierarchyPanel::changeMenu()
{
}
