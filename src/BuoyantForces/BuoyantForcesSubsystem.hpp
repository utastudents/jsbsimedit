#pragma once
#include "inc/Subsystem.hpp"
#include <gtkmm.h>

class BuoyantForcesSubsystem : public Subsystem
{
  public:
    std::string m_name;
    BuoyantForcesSubsystem(std::string N);
    void Create(); 
    void SetupTab(Gtk::Grid& p_grid);
    void AddUnitsDropDown(Gtk::Grid& p_grid, std::string label, int col, int row);
    void AddEntry(Gtk::Grid& p_grid, std::string label, int col, int row, bool hasDDMenu);

  protected:
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

    Gtk::Notebook m_notebook;
    std::vector<std::unique_ptr<Gtk::Grid>> m_pages;
};
