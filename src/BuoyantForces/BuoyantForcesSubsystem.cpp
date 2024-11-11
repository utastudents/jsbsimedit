#include <iostream>

#include "BuoyantForcesSubsystem.hpp"
#include "Component.hpp"


BuoyantForcesSubsystem::BuoyantForcesSubsystem(std::string N)
                :m_name(N)
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
  

  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), "Gas Cell");

  // Track switching tabs
  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
      &BuoyantForcesSubsystem::on_notebook_switch_page));
}



void BuoyantForcesSubsystem::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to BYF tab with index " << page_num << std::endl;
}

void BuoyantForcesSubsystem::on_dropdown_changed(const std::string& dropdown_name)
{
  auto& dropdown = m_dropdowns[dropdown_name];
  const auto selected = dropdown->get_selected();

  std::cout << "Dropdown '" << dropdown_name << "' changed Row = " << selected
            << ", String = " << (dropdown_name == "Gas Type" ?
                                  m_gasStringList->get_string(selected) :
                                  m_unitsStringList->get_string(selected))
            << std::endl;
}


void BuoyantForcesSubsystem::SetupTab(Gtk::Grid& p_grid) 
{
  // Drop Down Menu for Gas Type
  m_gasStringList = Gtk::StringList::create({"Air", "Helium", "Hydrogen"});
  auto label_gas = Gtk::make_managed<Gtk::Label>("Gas Type");

  m_dropdowns["Gas Type"] = std::make_unique<Gtk::DropDown>();
  m_dropdowns["Gas Type"]->set_model(m_gasStringList);
  m_dropdowns["Gas Type"]->set_selected(0);
  m_dropdowns["Gas Type"]->set_expand(false);
  m_dropdowns["Gas Type"]->set_show_arrow(true);
  m_dropdowns["Gas Type"]->set_size_request(150, -1);
  label_gas->set_size_request(250, -1);

  p_grid.attach(*label_gas, 0,0);
  p_grid.attach(*m_dropdowns["Gas Type"], 1, 0);

  m_dropdowns["Gas Type"]->property_selected().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), "Gas Type"));


  // Drop Down Menu for Units (for Location)
  AddUnitsDropDown(p_grid, "Location", 0, 1);

  // Entry Texts for Location
  auto input_location_x = AddEntry(p_grid, "x", 0, 3, false);
  input_location_x->signal_changed().connect([this,input_location_x]()
  {
    double locationX= std:: stod(input_location_x->get_text());
    
  });
  
  auto input_location_y = AddEntry(p_grid, "y", 0, 4, false);
  input_location_y->signal_changed().connect([this,input_location_y]()
  {
    double locationY= std:: stod(input_location_y->get_text());
    
  });

  auto input_location_z = AddEntry(p_grid, "z", 0, 5, false);
  input_location_z->signal_changed().connect([this,input_location_z]()
  {
    double locationZ= std:: stod(input_location_z->get_text());
  
  });


    // Drop Down Menu for Units (for Dimensions)
  AddUnitsDropDown(p_grid, "Dimensions", 0, 6);

  // Entry Texts for Dimensions
  auto input_dimension_x=AddEntry(p_grid, "x", 0, 7, false);
  input_dimension_x->signal_changed().connect([this,input_dimension_x]()
  {
    double dimensionX= std:: stod(input_dimension_x->get_text());
  
  });

  auto input_dimension_y=AddEntry(p_grid, "y", 0, 8, false);
  input_dimension_y->signal_changed().connect([this,input_dimension_y]()
  {
    double dimensionY= std:: stod(input_dimension_y->get_text());
  
  });

  auto input_dimension_z=AddEntry(p_grid, "z", 0, 9, false);
  input_dimension_z->signal_changed().connect([this,input_dimension_z]()
  {
    double dimensionZ= std:: stod(input_dimension_z->get_text());
  
  });

  // Entry Text for Max Overpressure
  //gui dispaly text input field
  auto input_max_overpressure= AddEntry(p_grid, "Max Overpressure", 0, 10, true);

  //conect input to a class variable
  input_max_overpressure->signal_changed().connect([this, input_max_overpressure]()
        {
                maxOverpressure=std::stod(input_max_overpressure->get_text());//stores value

        });

  // Entry Text for Valve Coefficient
  // gui display text input field
  auto input_valve_coefficient= AddEntry(p_grid, "Valve Coefficient", 0, 11, true);


  input_valve_coefficient->signal_changed().connect([this,input_valve_coefficient](){
        valveCoefficient=std::stod(input_valve_coefficient->get_text());
        });


  // Entry Text for Fullness
  AddEntry(p_grid, "Fullness", 0, 12, false);

  if (m_pages.size() == 1) {
    // Select # of Ballonets
    Glib::RefPtr<Gtk::StringList> m_ballonetStringList;

    const std:: vector<Glib::ustring> ballonetOptions = {"0","1","2","3","4","5"};
    auto label_ballonet = Gtk::make_managed<Gtk::Label>("Ballonet");

    m_ballonetStringList = Gtk ::StringList::create(ballonetOptions);

    m_dropdowns["Ballonet"] = std::make_unique<Gtk::DropDown>();
    m_dropdowns["Ballonet"]->set_model(m_ballonetStringList);
    m_dropdowns["Ballonet"]->set_selected(0);

    m_dropdowns["Ballonet"]->set_expand(false);
    m_dropdowns["Ballonet"]->set_show_arrow(true);
    m_dropdowns["Ballonet"]->set_size_request(150, -1);

    m_dropdowns["Ballonet"]->property_selected().signal_changed().connect(sigc::mem_fun(*this,&BuoyantForcesSubsystem:: on_ballonetcount_changed));
    label_ballonet->set_size_request(250, -1);

    p_grid.attach(*label_ballonet, 0,13);
    p_grid.attach(*m_dropdowns["Ballonet"],1,13);
  } else {

    // Input Blower Input
    auto input_blower_value = AddEntry(p_grid, "Blower input", 0, 13, false);
    input_blower_value->signal_changed().connect([this,input_blower_value]()
    {
      blowerInput= std::stod(input_blower_value->get_text());
    });

  }
  
}

void BuoyantForcesSubsystem:: on_ballonetcount_changed()
{
  int selected_value = m_dropdowns["Ballonet"]->get_selected();
  if(selected_value >= 0)
  {
  int ballonetCount= selected_value;
  Component :: setBallonetCount(ballonetCount);
  std::cout << "Selected Ballonet Count:" <<ballonetCount <<std::endl;

  BuildTabs();
  
  }

}

void BuoyantForcesSubsystem::BuildTabs() 
{
  std::cout << "in BuoyantForcesSubsystem::BuildTabs" << std::endl;

  
  
  for (int i = 0; i < Component::getBallonetCount(); i++) 
  {
    Gtk::Grid grid;
    grid.set_row_spacing(10);
    grid.set_column_spacing(10);
    //m_notebook.append_page(grid, "Ballonet " + std::to_string(i+1));
    m_pages.push_back(std::make_unique<Gtk::Grid>());
    SetupTab(*m_pages.back());
    m_notebook.append_page(*m_pages.back(), "Ballonet" + std::to_string(i+1));

  
  }

}



void BuoyantForcesSubsystem::AddUnitsDropDown(Gtk::Grid& p_grid, std::string label, int col, int row) {
  m_unitsStringList = Gtk::StringList::create({});
  auto dropdown_label = Gtk::make_managed<Gtk::Label>(label);

  for (int i = static_cast<int>(Component::Unit::WIDTH); i <= static_cast<int>(Component::Unit::FT3_SEC); ++i)
  {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_unitsStringList->append(Component::unitToString(unit));
  }

  m_dropdowns[label] = std::make_unique<Gtk::DropDown>();
  m_dropdowns[label]->set_model(m_unitsStringList);
  m_dropdowns[label]->set_selected(3);
  m_dropdowns[label]->set_expand(false);
  m_dropdowns[label]->set_show_arrow(true); 

  p_grid.attach(*dropdown_label, col, row);
  p_grid.attach(*m_dropdowns[label], ++col, row);

  m_dropdowns[label]->property_selected().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), label));
}

Gtk::Entry* BuoyantForcesSubsystem::AddEntry(Gtk::Grid& p_grid, std::string label, int col, int row, bool hasDDMenu)
{
  auto entry_number = Gtk::make_managed<Gtk::Entry>();
  auto entry_label = Gtk::make_managed<Gtk::Label>(label);

  entry_number->set_max_length(50);
  entry_number->select_region(0, entry_number->get_text_length());
  entry_number->set_expand(false);
  entry_number->set_input_purpose(Gtk::InputPurpose::NUMBER);

  p_grid.attach(*entry_label, col, row);
  p_grid.attach(*entry_number, ++col, row);

  if (hasDDMenu) {
    AddUnitsDropDown(p_grid, "", ++col, row);
  }

	return entry_number;
}

