#include "MenuPanel.hpp"
#include <sstream>
#include <iostream>

TableMenu::TableMenu(std::shared_ptr<AerodynamicsNode> node)
    : table(std::dynamic_pointer_cast<Table>(node)) {
    if (!table) {
        throw std::runtime_error("Node is not of type Table.");
    }

    // Set the header
    setHeader("Table Menu");

    // Create a scrolled window for the TreeView
    auto scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolled_window->set_min_content_height(300);
    scrolled_window->set_min_content_width(500);
    append(*scrolled_window);

    // Create the TreeView
    tree_view = Gtk::make_managed<Gtk::TreeView>();
    scrolled_window->set_child(*tree_view);

    // Set up the ListStore model
    list_store = Gtk::ListStore::create(columns);
    tree_view->set_model(list_store);

    // Add columns to the TreeView
    setup_columns();

    // Populate the table with data
    populate_table();
}

void TableMenu::setup_columns() {
    tree_view->append_column("Column 1", columns.col1);
    tree_view->append_column("Column 2", columns.col2);
}

void TableMenu::populate_table() {
    list_store->clear();

    // Get data from the table node
    std::istringstream data_stream(table->getTableData());
    std::string line;

    while (std::getline(data_stream, line)) {
        std::istringstream line_stream(line);
        std::string col1_data, col2_data;

        line_stream >> col1_data >> col2_data;

        auto row = *(list_store->append());
        row[columns.col1] = col1_data;
        row[columns.col2] = col2_data;
    }

    std::cout << "Table populated successfully!" << std::endl;
}
