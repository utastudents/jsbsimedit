#pragma once
#include "inc/XML_api.hpp"
#include "inc/Subsystem.hpp"
#include <gtkmm.h>
#include <unordered_map>
#include "GasCell.hpp"
#include "Ballonet.hpp"
#include "Component.hpp"

#include "XML/XMLDoc.hpp" //temporary


class BuoyantForcesSubsystem : public Subsystem
{
  public:
    BuoyantForcesSubsystem();
    void Create(); 

  protected:
    Component::Unit GetUnitFromString(const std::string& unit_string) const;
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);
    void on_dropdown_changed(const std::string& dropdown_name);
    void on_entry_activate(const std::string& key);
    void on_ballonetcount_changed();
    void LoadStringLists();
    void AddDropDown(Gtk::Grid& p_grid, std::string label, int col, Glib::RefPtr<Gtk::StringList> stringlist);
    void BuildTabs();
    void SetupTab(Gtk::Grid& p_grid);
    void AddEntry(Gtk::Grid& p_grid, std::string label, bool hasDDMenu);
    void loadXmlData();
    void saveXmlData();


    Gtk::Notebook m_notebook;
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
  	double maxOverpressure;
    double valveCoefficient;
    Component::Unit maxOverpressureUnit;
    Component::Unit valveCoefficientUnit;
    double locationX;
    double locationY;
    double locationZ;
    double dimensionX;
    double dimensionY;
    double dimensionZ;
    double blowerInput;
    
    //temporary
    JSBEdit::XMLDoc doc;

    GasCell m_gascell;
    std::vector<Ballonet> m_ballonets;
    static int m_rows;
    static int m_tab_count;
  };
