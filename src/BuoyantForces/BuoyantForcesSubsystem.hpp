#pragma once
#include "inc/Subsystem.hpp"
#include <gtkmm.h>

class BuoyantForcesSubsystem : public Subsystem
{
  public:
    std::string m_name;
    BuoyantForcesSubsystem(std::string N);
    void Create(); 
    void setupGasCellTab();
    void BuildTabs();

  protected:
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

    Gtk::Notebook m_notebook;
    std::vector<std::unique_ptr<Gtk::Box>> m_pages;
    Gtk::DropDown m_gasMenu;
};
