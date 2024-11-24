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
    // Gtk::Grid gridLayout;,,,not needed
    Gtk::Box m_VBox;
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
    
    //Gtk::ScrolledWindow scrolledWindowV; // Vertical scrolling window for property list
    //Gtk::ScrolledWindow scrolledWindowH; // Horizontal scrolling window for property list

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
    // Gtk::TreeModelColumn<Glib::ustring> index, propertyName, description, unit, access, comments;
        
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
