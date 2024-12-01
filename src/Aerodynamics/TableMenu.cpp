#include "MenuPanel.hpp"
#include <sstream>
#include <iostream>

// Constructor
TableMenu::TableMenu(std::shared_ptr<AerodynamicsNode> node)
    : table(std::dynamic_pointer_cast<Table>(node)) {
    if (!table) {
        throw std::runtime_error("Node is not of type Table.");
    }

    /*

    // Set the header
    setHeader("Table");

    // Create a grid layout for table content
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    // Add a scrolled window for the TreeView
    auto scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolled_window->set_min_content_height(300);
    scrolled_window->set_min_content_width(500);
    grid->attach(*scrolled_window, 0, 0);

    // Create a TreeView to display the table data
    auto tree_view = Gtk::make_managed<Gtk::TreeView>();
    scrolled_window->set_child(*tree_view);

    // Set up the ListStore model
    auto list_store = Gtk::ListStore::create(Gtk::TreeModel::ColumnRecord());
    tree_view->set_model(list_store);

    // Initialize columns and populate the TreeView
    setup_columns(tree_view, list_store);
    populate_table(tree_view, list_store);

    // Connect update signal to refresh the table on data changes
    update_signal.connect([this, tree_view, list_store]() {
        populate_table(tree_view, list_store);
    });

    // Debugging: Print the table data
    std::cout << "Table data loaded:\n" << table->getTableData() << std::endl;

    */
}

/*

// Set up TreeView columns based on the table data
void TableMenu::setup_columns(Gtk::TreeView* tree_view, Glib::RefPtr<Gtk::ListStore> list_store) {
    std::stringstream ss(table->getTableData());
    std::string line;

    // Read the first row to determine the number of columns
    if (std::getline(ss, line)) {
        std::istringstream line_stream(line);
        std::string value;
        int col_idx = 0;

        while (line_stream >> value) {
            auto column = Gtk::TreeModelColumn<std::string>();
            tree_view->append_column("Column " + std::to_string(++col_idx), column);
            list_store->add_column(column);

            std::cout << "Added column: Column " << col_idx << std::endl;
        }
    }
}

// Populate the table with data from the `Table` node
void TableMenu::populate_table(Gtk::TreeView* tree_view, Glib::RefPtr<Gtk::ListStore> list_store) {
    std::cout << "Populating table..." << std::endl;
    list_store->clear();
    std::stringstream ss(table->getTableData());
    std::string line;

    // Parse each row of data
    int row_index = 0;
    while (std::getline(ss, line)) {
        auto iter = list_store->append();
        std::istringstream line_stream(line);
        std::string value;
        int col_idx = 0;

        while (line_stream >> value) {
            (*iter)[tree_view->get_column(col_idx++)->get_model_column()] = value;
        }

        std::cout << "Row " << row_index++ << " populated: " << line << std::endl;
    }
    std::cout << "Table population complete." << std::endl;
}

*/