#pragma once

#include <gtkmm.h>

class HierarchyPanel: public Gtk::Box{
private:
    Gtk::TreeView treeView;
    //Gtk::TreeStore tree;
    Gtk::ScrolledWindow scrolledWindow;
public:
    HierarchyPanel();
    void populateTree();
    void changeMenu();
};
