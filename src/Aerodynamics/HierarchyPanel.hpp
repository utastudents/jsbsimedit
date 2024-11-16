#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"

class HierarchyPanel : public Gtk::ScrolledWindow {
public:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { add(columnName), add(node); }
        Gtk::TreeModelColumn<Glib::ustring> columnName;
        Gtk::TreeModelColumn<std::shared_ptr<AerodynamicsNode>> node;
    };
    ModelColumns columns;
    HierarchyPanel();
    void populateTree(Glib::RefPtr<Gtk::TreeStore> treeStore);
    void changeMenu();
    const ModelColumns& getColumns();
private:
    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
};

