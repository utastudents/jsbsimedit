#pragma once

#include <gtkmm.h>

class HierarchyPanel: public gtkmm::box{
private:
    gtkmm::TreeView treeView;
    gtkmm::TreeStore tree;
    gtkmm::ScrolledWindow scrolledWindow;
public:
    HierarchyPanel();
    void populateTree();
    void changeMenu();
};