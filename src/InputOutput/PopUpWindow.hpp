#pragma once
#include <gtkmm.h>
#include "inc/XML_api.hpp"
#include "XML/XMLDoc.hpp"

class PopUpWindow : public Gtk::Window {
public:
    PopUpWindow();
    virtual ~PopUpWindow();

    std::string getSelectedProperty(); // New method to return the selected property

protected:
    void onFilterButtonClicked();
    void onShowAllButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();
    void applyFilter(); // Apply filtering logic
    void updateShowHideCounts(); // Update counts of shown/hidden properties
    void onPropertySelected(); // Handle property selection

private:
    // Widgets
    Gtk::Box m_VBox;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView propertyTreeView;

    // Labels and Entry
    Gtk::Label currentLabel;
    Gtk::Label showLabel;
    Gtk::Label hideLabel;
    Gtk::Entry filterTextBox;

    // Buttons
    Gtk::Button filterButton;
    Gtk::Button showAllButton;
    Gtk::Button okButton;
    Gtk::Button cancelButton;

    // Grids
    Gtk::Grid* filterGrid;
    Gtk::Grid* buttonGrid;

    // Current Placeholder for selected property
    Gtk::Entry* currentPlaceholder;

    // Properties
    std::vector<std::string> properties;

    // Store the selected property
    std::string selectedProperty;

    // TreeView Columns
    class PropertyColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        PropertyColumns() {
            add(index);
            add(propertyName);
            add(description);
            add(unit);
            add(access);
            add(comments);
        }
        Gtk::TreeModelColumn<int> index;  // Use int for the "No." column
        Gtk::TreeModelColumn<Glib::ustring> propertyName;
        Gtk::TreeModelColumn<Glib::ustring> description;
        Gtk::TreeModelColumn<Glib::ustring> unit;
        Gtk::TreeModelColumn<Glib::ustring> access;
        Gtk::TreeModelColumn<Glib::ustring> comments;
    };

    PropertyColumns propertyColumns;
    Glib::RefPtr<Gtk::ListStore> listStore;
};

