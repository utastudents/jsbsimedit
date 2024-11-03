#include <iostream>

#include "BuoyantForcesSubsystem.hpp"

BuoyantForcesSubsystem::BuoyantForcesSubsystem(std::string N)
                :m_name(N),
                m_Label1("Contents for gas cell"),
                m_Label2("Contents for ballonet 1"),
                m_Label3("Contents for ballonet 2"),
                m_Label4("Contents for ballonet 3")
{
    std::cout << "In BuoyantForcesSubsystem contructor" << std::endl; 
}

void BuoyantForcesSubsystem::Create()
{
  std::cout << "in BuoyantForcesSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  m_Notebook.set_margin(10);
  m_Notebook.set_expand();

  m_Grid.attach(m_Notebook, 0, 0);

  m_Notebook.append_page(m_Label1, "Gas Cell");
  m_Notebook.append_page(m_Label2, "Ballonet 1");
  m_Notebook.append_page(m_Label3, "Ballonet 2");
  m_Notebook.append_page(m_Label4, "Ballonet 3");

  m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
             &BuoyantForcesSubsystem::on_notebook_switch_page) );

  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  // for (int i = 0; i < 14; i++)
  // {
  //   for (int j = 0; j < 15; j++)
  //   {
  //     auto s = Glib::ustring::compose("button (%1,%2)", i, j);
  //     auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
  //     m_Grid.attach(*pButton, i, j);
  //   }
  // }


}

void BuoyantForcesSubsystem::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;

  //You can also use m_Notebook.get_current_page() to get this index.
}
