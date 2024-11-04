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

    Gtk::Notebook m_Notebook;
    Gtk::Label m_Label1, m_Label2, m_Label3, m_Label4;
};
