#pragma once

#include <gtkmm.h>

class HierarchyPanel : public Gtk::ScrolledWindow {
private:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { add(columnName); }
        Gtk::TreeModelColumn<Glib::ustring> columnName;
    };

    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
    ModelColumns columns;

public:
    HierarchyPanel();
    void populateTree();
    void changeMenu();
};

