#pragma once
#include <gtkmm.h>
#include "inc/XML_api.hpp"
#include "XML/XMLDoc.hpp"

class PopUpWindow : public Gtk::Window { // Explicitly inherit from Gtk::Window
public:
    PopUpWindow();
    virtual ~PopUpWindow();

    std::string getSelectedProperty(); // New method to return the selected property

protected:
    void onButtonClicked(); // handler for button click actions
    void onFilterButtonClicked();
    void onShowAllButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();
    void loadPropertiesFromFile(const std::string& filePath);
    void onPropertySelected();
    void updateShowHideCounts();
    void applyFilter(); // Helper method

private:
    // Widgets
    Gtk::Box m_VBox;
    Gtk::Label currentLabel;
    Gtk::Entry* currentPlaceholder;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::Grid m_Grid;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TreeView propertyTreeView;
    Gtk::Label filterLabel;
    Gtk::Window propertiesScrolledWindow;
    Gtk::Label currentPropertyValue;
    Gtk::Entry filterTextBox; 
    Gtk::Button filterButton; 
    Gtk::Button showAllButton; 
    Gtk::Button okButton; 
    Gtk::Button cancelButton; 
    Gtk::Button closeButton;
    int visibleProperties; 
    int hiddenProperties; 
    Gtk::Label showLabel;
    Gtk::Label hideLabel;

    // Define property columns model
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

    std::string selectedProperty; // New private member to store the selected property
};

