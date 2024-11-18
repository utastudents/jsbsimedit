#pragma once

#include <gtkmm.h>
#include "HierarchyPanel.hpp"
#include "MenuPanel.hpp"
#include "AerodynamicsNode.hpp"
#include "XML/XMLNode.hpp"
#include "inc/XML_api.hpp"

class AerodynamicsWidget : public Gtk::Paned {
private:
    Glib::RefPtr<Gtk::TreeStore> aerodynamicsNodes;
    HierarchyPanel hierarchyPanel;
    MenuPanel menuPanel;
    AerodynamicsNode* selectedNode;
    const HierarchyPanel::ModelColumns& columns = hierarchyPanel.getColumns();

    void fetchData();
    void saveData();
    void appendChildren(Gtk::TreeRow parent, std::vector<JSBEdit::XMLNode> children);
public:
    AerodynamicsWidget();
};
