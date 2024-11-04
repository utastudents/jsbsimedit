#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"

class BuoyantForcesSubsystem : public Subsystem
{
  public:
    std::string m_name;
    BuoyantForcesSubsystem(std::string N);
    void Create(); 

  protected:
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

    Gtk::Notebook m_notebook;
    Gtk::Label m_label1, m_label2, m_label3, m_label4;
    Gtk::DropDown m_gasTypeMenu;
    Gtk::Box m_box1;
};
