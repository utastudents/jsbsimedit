#pragma once

#include <gtkmm.h>
#include "HierarchyPanel.hpp"
#include "MenuPanel.hpp"
#include "AerodynamicsNode.hpp"
#include "XML/XMLNode.hpp"
#include "inc/XML_api.hpp"

// Class representing the Aerodynamics widget with tree and menu panels
class AerodynamicsWidget : public Gtk::Paned {
private:
    // Data model for aerodynamics nodes
    Glib::RefPtr<Gtk::TreeStore> aerodynamicsNodes;

    // Panels for displaying hierarchy and menu
    HierarchyPanel hierarchyPanel;
    MenuPanel menuPanel;

    // Pointer to the currently selected aerodynamics node
    AerodynamicsNode* selectedNode;

    // Reference to the column definitions from the HierarchyPanel
    const HierarchyPanel::ModelColumns& columns = hierarchyPanel.getColumns();

    // Private methods for managing data
    void fetchData();
    void saveData();
    void appendChildren(Gtk::TreeRow parent, std::vector<JSBEdit::XMLNode> children); // Helper function that appends child nodes to a tree

public:
    // Constructor for AerodynamicsWidget
    AerodynamicsWidget();
};
