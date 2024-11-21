#pragma once
#include <gtkmm.h>


class PopUpWindow : public Gtk::Window { // Explicitly inherit from Gtk::Window
public:
    PopUpWindow();
    virtual ~PopUpWindow();

protected:

    void onButtonClicked(); // handler for button click actions
    void onFilterButtonClicked();
    void onShowAllButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();
    void loadPropertiesFromFile(const std::string& fileName);

   // Helper methods
    void applyFilter();
    
private:
    // Widgets
    Gtk::Grid gridLayout;
    Gtk::ScrolledWindow scrolledWindow; 
    Gtk::TreeView propertyTreeView;
    Gtk::Label filterLabel;
    Gtk::Label currentPropertyValue; // Displays currently selected property
    Gtk::Entry filterTextBox; // Input field for filtering properties
    Gtk::Button filterButton; // Button to filter the list of properties
    Gtk::Button showAllButton; // Button to reset and show all properties
    Gtk::Button okButton; // OK button, confirms selection and closes pop-up
    Gtk::Button cancelButton; // Cancel button, discards changes and closes pop-up
    Gtk::Button closeButton; // Close button, closes the pop-up window
    int visibleProperties; // Count of visible properties after filtering
    int hiddenProperties; // Count of hidden properties after filtering
    Gtk::ScrolledWindow scrolledWindowV; // Vertical scrolling window for property list
    Gtk::ScrolledWindow scrolledWindowH; // Horizontal scrolling window for property list

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
        Gtk::TreeModelColumn<Glib::ustring> index, propertyName, description, unit, access, comments;
    };

    PropertyColumns propertyColumns;
    Glib::RefPtr<Gtk::ListStore> listStore;
    
};
