#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"

// Class representing a scrollable panel with a tree hierarchy of nodes
class HierarchyPanel : public Gtk::ScrolledWindow {
public:
    // Defining the columns for the TreeModel
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { 
            add(columnName); 
            add(node); 
        }
        Gtk::TreeModelColumn<Glib::ustring> columnName; // Column for node names
        Gtk::TreeModelColumn<std::shared_ptr<AerodynamicsNode>> node; // Column for AerodynamicsNode objects
    };

    // Constructor
    HierarchyPanel();

    // Populates the tree view with data from the given TreeStore
    void populateTree(Glib::RefPtr<Gtk::TreeStore> treeStore);

    // Getter for the ModelColumns
    const ModelColumns& getColumns();

private:
    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
    ModelColumns columns;
};
