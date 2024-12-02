#pragma once

#include <gtkmm.h>
#include "AerodynamicsNode.hpp"
#include <iostream>

class MenuPanel : public Gtk::Box {
private:
    Gtk::Label* header;
public:
    MenuPanel() : Gtk::Box(Gtk::Orientation::VERTICAL)
    {
        // Creates a header for the menu
        header = Gtk::make_managed<Gtk::Label>();
        header->set_halign(Gtk::Align::CENTER);
        append(*header);
    }
    ~MenuPanel(){}

    void setHeader(std::string title){header->set_label(title);}

    using UpdateSignal = sigc::signal<void()>;
    UpdateSignal update_signal;
};

class FunctionMenu : public MenuPanel {
public:
    FunctionMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<Function> function;
    Gtk::Entry* nameEntry;
    Gtk::Entry* descriptionEntry;
    Gtk::ComboBoxText* dropdown;
};

class TableMenu : public MenuPanel {
public:
    TableMenu(std::shared_ptr<AerodynamicsNode> node);

private:
    void setup_columns();
    void populate_table();

    std::shared_ptr<Table> table;
    Glib::RefPtr<Gtk::ListStore> list_store;
    Gtk::TreeView* tree_view;
    Gtk::Grid* grid;
    Gtk::Label* rowPropertyLabel;
    Gtk::Label* columnPropertyLabel;
    Gtk::Entry* rowPropertyEntry;
    Gtk::Entry* columnPropertyEntry;

    // Column structure for TreeView
    class TableColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        Gtk::TreeModelColumn<std::string> col1;
        Gtk::TreeModelColumn<std::string> col2;

        TableColumns() {
            add(col1);
            add(col2);
        }
    };

    TableColumns columns;
};


class ValueMenu : public MenuPanel {
public:
    ValueMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    Gtk::Label* inputLabel;
    Gtk::Entry* inputEntry;
    std::shared_ptr<Value> value;
    void on_text_changed();
};

class AxisMenu : public MenuPanel {
public:
    AxisMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    void on_name_dropdown_selected();
    void on_unit_dropdown_selected();
    std::shared_ptr<Axis> axis;
    Gtk::Grid* grid;
    Gtk::Label* nameDropdownLabel;
    Gtk::DropDown* nameDropdown;
    Gtk::Label* unitDropdownLabel;
    Gtk::DropDown* unitDropdown;
    std::shared_ptr<Gtk::StringList> name_list;
    std::shared_ptr<Gtk::StringList> unit_list;
};

class PropertyMenu : public MenuPanel {
public:
    PropertyMenu(std::shared_ptr<AerodynamicsNode> node);
private:
    std::shared_ptr<AeroProperty> property;
    void onButtonClicked(); // handler for button click actions
    void onFilterButtonClicked();
    void onShowAllButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();
    void loadPropertiesFromFile(const std::string& fileName);
    void onPropertySelected();
    void addProperty();
    void reloadList();
   // Helper methods
    void applyFilter();
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
