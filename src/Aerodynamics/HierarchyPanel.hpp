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

    // Signal type that takes a reference to the selected AerodynamicsNode
    using RowActivatedSignal = sigc::signal<void(std::shared_ptr<AerodynamicsNode>)>;
    RowActivatedSignal row_activated_signal;

private:
    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
    ModelColumns columns;

    // Method to handle row selection
    void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
};
