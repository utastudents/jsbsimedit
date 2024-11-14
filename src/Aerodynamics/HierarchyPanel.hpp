#pragma once

#include <gtkmm.h>

class HierarchyPanel : public Gtk::ScrolledWindow {
public:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { add(columnName); }
        Gtk::TreeModelColumn<Glib::ustring> columnName;
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

