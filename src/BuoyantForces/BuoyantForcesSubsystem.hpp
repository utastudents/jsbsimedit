#pragma once
#include "inc/Subsystem.hpp"
#include <gtkmm.h>
#include "Component.hpp"
class BuoyantForcesSubsystem : public Subsystem
{
  public:
    std::string m_name;
    BuoyantForcesSubsystem(std::string N);
    void Create(); 
    void SetupTab(Gtk::Grid& p_grid);
    void AddUnitsDropDown(Gtk::Grid& p_grid, std::string label, int col, int row);
    Gtk::Entry* AddEntry(Gtk::Grid& p_grid, std::string label, int col, int row, bool hasDDMenu);
    void on_ballonetcount_changed();
    void BuildTabs();

  protected:
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);
    void on_dropdown_changed(const std::string& dropdown_name);

    Gtk::Notebook m_notebook;
    Glib::RefPtr<Gtk::StringList> m_ballonetStringList;
    std::vector<std::unique_ptr<Gtk::Grid>> m_pages;
    std::map<std::string, std::unique_ptr<Gtk::DropDown>> m_dropdowns;
    Glib::RefPtr<Gtk::StringList> m_gasStringList;
    Glib::RefPtr<Gtk::StringList> m_unitsStringList;

 private:
  	double maxOverpressure;
    double valveCoefficient;
    Component::Unit maxOverpressureUnit;
    Component::Unit valveCoefficientUnit;

};
