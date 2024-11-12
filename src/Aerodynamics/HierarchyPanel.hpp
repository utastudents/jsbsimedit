#pragma once

#include <gtkmm.h>

class HierarchyPanel : public Gtk::Box {
private:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { add(columnName); }
        Gtk::TreeModelColumn<Glib::ustring> columnName;
    };

    Gtk::TreeView treeView;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
    Gtk::ScrolledWindow scrolledWindow;
    ModelColumns columns;

public:
    HierarchyPanel();
    void populateTree();
    void changeMenu();
};

