#pragma once
#include "inc/XML_api.hpp"
#include "inc/Subsystem.hpp"
#include <gtkmm.h>
#include <unordered_map>
#include <format>
#include "BuoyantForces.hpp"
#include "GasCell.hpp"
#include "Ballonet.hpp"
#include "Component.hpp"

#include "XML/XMLDoc.hpp" //temporary
#include "XML/XMLLoad.hpp"


class BuoyantForcesSubsystem : public Subsystem
{
  public:
    BuoyantForcesSubsystem();
    void Create(); 
    void SaveXMLData();
    void LoadXMLData();
    void UpdateData();

  protected:
    // Signal Handlers
    void on_button_toggled();
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);
    void on_dropdown_changed(const std::string& dropdown_name);
    void on_entry_activate(const std::string& key);

    // Helper Methdos for Save and Load
    void SetNodesFromWidgets(JSBEdit::XMLNode& parent);
    void SetWidgetsFromNodes(JSBEdit::XMLNode& root, int tabIndex);
    void SetDropDownFromNode(JSBEdit::XMLNode& node, const std::string& nodeName, const std::string& attributeName,
                             const Glib::RefPtr<Gtk::StringList>& stringList, const std::string& dropdownLabel,
                             int tabIndex);
    void SetEntryFromNode(JSBEdit::XMLNode& node, const std::string& nodeName,
                          const std::string& entryLabel, int tabIndex);

    void LoadStringLists();
    void BuildTabs(int target);
    void SetupTab(Gtk::Grid& p_grid);
    void AddDropDown(Gtk::Grid& p_grid, std::string label, int col, Glib::RefPtr<Gtk::StringList> stringlist);
    void AddEntry(Gtk::Grid& p_grid, std::string label, bool hasDDMenu);
    Component::Unit stringToUnit(const std::string& unit_string) const;

    // Methods for Testing (Temporary)
    void on_button_clicked(const std::string& button_name);


    Gtk::Notebook m_notebook;
    Gtk::CheckButton m_checkbutton;
    std::unordered_map<std::string, std::unique_ptr<Gtk::Grid>> m_pages;
    std::unordered_map<std::string, std::unique_ptr<Gtk::DropDown>> m_dropdowns;
    std::unordered_map<std::string, std::unique_ptr<Gtk::Entry>> m_entries;
    Glib::RefPtr<Gtk::StringList> m_ballonetStringList;
    Glib::RefPtr<Gtk::StringList> m_gasStringList;
    Glib::RefPtr<Gtk::StringList> m_shapeStringList;
    Glib::RefPtr<Gtk::StringList> m_measurementStringList;
    Glib::RefPtr<Gtk::StringList> m_pressureStringList;
    Glib::RefPtr<Gtk::StringList> m_valveStringList;
    Glib::RefPtr<Gtk::StringList> m_blowerStringList;

 private:
    //temporary
    JSBEdit::XMLDoc m_doc;
    Gtk::Button m_savebutton;
    Gtk::Button m_loadbutton;

    BuoyantForces m_buoyantforces;
    GasCell m_gascell;
    std::vector<Ballonet> m_ballonets;
    static int m_rows;
    static int m_tab_count;
  };
