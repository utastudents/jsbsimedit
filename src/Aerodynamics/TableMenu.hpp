#pragma once

#include "MenuPanel.hpp"
#include "GraphArea.hpp"
#include <gtkmm.h>
#include <memory>

class TableMenu : public MenuPanel {
public:
    // Constructor
    TableMenu(std::shared_ptr<AerodynamicsNode> node);

private:
    // Methods
    void setup_graph();

    // Data Members
    std::shared_ptr<Table> table;               // Node providing data
    Gtk::ScrolledWindow* graph_scrolled_window; // Scrollable container for the graph
};
