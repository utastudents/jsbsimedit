#include <iostream>

#include "BuoyantForcesSubsystem.hpp"
#include "Component.hpp"

BuoyantForcesSubsystem::BuoyantForcesSubsystem(std::string N)
                :m_name(N),
                m_label1("Contents for gas cell"),
                m_label2("Contents for ballonet 1"),
                m_label3("Contents for ballonet 2"),
                m_label4("Contents for ballonet 3")
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

  m_notebook.set_margin(10);
  m_notebook.set_expand();

  m_Grid.attach(m_notebook, 0, 0);

  m_notebook.append_page(m_label1, "Gas Cell");
  m_notebook.append_page(m_label2, "Ballonet 1");
  m_notebook.append_page(m_label3, "Ballonet 2");
  m_notebook.append_page(m_label4, "Ballonet 3");

  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
             &BuoyantForcesSubsystem::on_notebook_switch_page) );

  m_Grid.attach(m_gasTypeMenu, 0, 1);

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

// void BuoyantForcesSubsystem::page_setup(Gtk::Widget*, guint page_num)
// {

// }
void BuoyantForcesSubsystem::setupGasCellTab()
{	//creating the widgets for the cell tabl
	Gtk::Box gasCellBox(Gtk::ORIENTATION_VERTICAL, 10);
	// create lavel for gas cell tab
    	Gtk::Label gasCellNameLabel("Gas Cell: ");
	gasCellNameLabel.set_halign(Gtk::ALIGN_START);
	gasCellBox.pack_start(gasCellNameLabel);
	//next creating the drop down menu
	Gtk::Label gasTypeLabel("Select Gas Type:");
	gasTypeLabel.set_halign(Gtk::ALIGN_START);
	gasCellBox.pack_start(gasTypeLabel);
	m_gasTypeMenu.append("Air");//adding elements to drop down menu
	m_gasTypeMenu.append("Helium");
	m_gasTypeMenu.append("Hydrogen");
	m_gasTypeMenu.set_active(0); // Set default to Air
	gasCellBox.pack_start(m_gasTypeMenu);






}
