#include <iostream>

#include "MetricsSubsystem.hpp"

MetricsSubsystem::MetricsSubsystem()
{
  m_Name = "Metrics";
  std::cout << "In MetricsSubsystem contructor" << std::endl;
      std::map<std::string, Metrics::string_vector> unit_map{
      {"wingarea", {"FT2", "M2"}},
      {"wingspan", {"FT", "M"}},
      {"wing_incidence", {"FT", "M"}},
      {"chord", {"DEG"}},
      {"htailarea", {"FT2", "M2"}},
      {"htailarm", {"FT", "M"}},
      {"vtailarea", {"FT2", "M2"}},
      {"vtailarm", {"FT", "M"}},
      {"location", {"IN", "FT", "M"}}};


  // Create and initialize Metrics::Data_Unit instances
  std::string node_name{""};

  node_name = "Wingarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "Wingspan";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(76.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "Chord";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "htailarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "htailarm";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "vtailarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "vtailarm";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  // Create and initialize Metrics::Data_Unit instance
  node_name = "Wing_Incidence";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);
  data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
  data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  // Create and initialize Metrics::Vertex_Unit instances
  node_name = "Aerodynamic Reference Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.1, 0.2, 0.3, unit_map["location"]);
  vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "Eye Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.4, 0.5, 0.6, unit_map["location"]);
  vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.

  node_name = "Visual Reference Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.7, 0.8, 0.9, unit_map["location"]);
  vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
  // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
  // Otherwise read in current unit from XML and use that if it is valid.
}

void MetricsSubsystem::Create()
{
  std::cout << "in MetricsSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  // for (int i = 0; i < 10; i++)
  // {
  //   for (int j = 0; j < 10; j++)
  //   {
  //     auto s = Glib::ustring::compose("button (%1,%2)", i, j);
  //     auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
  //     m_Grid.attach(*pButton, i, j);
  //   }
  // }
  

  int row = 0;
  for (auto cit = data_units.cbegin(); cit != data_units.cend(); cit++)
  {
    add_data_unit(cit->first, cit->second->get_its_unit()->get_unit_bank(), row++, 0);
  }

  // Add widgets for vertex data units
  row++; // Add an empty row between data units and vertex data units
  for (auto cit = vertex_data_units.cbegin(); cit != vertex_data_units.cend(); cit++) {
    add_vertex_data_unit(cit->first, cit->second->get_its_unit()->get_unit_bank(), row, 0);
    row += 4; 
  }


}

void MetricsSubsystem::add_vertex_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horizontal_position) {
  auto section_label = Gtk::make_managed<Gtk::Label>(tab_name);
  m_Grid.attach(*section_label, horizontal_position, vertical_position, 6, 1); 

  // Add X, Y, and Z entry boxes
  for (int i = 0; i < 3; i++) {
    std::string coordinate = i == 0 ? "X: " : (i == 1 ? "Y: " : "Z: ");
    auto x_label = Gtk::make_managed<Gtk::Label>(coordinate);
    m_Grid.attach(*x_label, horizontal_position + i * 2, vertical_position + 1, 1, 1);

    auto entry_number = Gtk::make_managed<Gtk::Entry>();
    entry_number->set_expand(false);
    entry_number->set_input_purpose(Gtk::InputPurpose::NUMBER);
    entry_number->set_max_length(15);
    entry_number->select_region(0, entry_number->get_text_length());
    m_Grid.attach(*entry_number, horizontal_position + i * 2 + 1, vertical_position + 1, 1, 1);
  }

  // Add the unit dropdown 
  auto unit_label = Gtk::make_managed<Gtk::Label>("Unit: ");
  m_Grid.attach(*unit_label, horizontal_position + 6, vertical_position + 1, 1, 1);

  auto dropdown_bank = Gtk::StringList::create({});
  for (auto cit = units.cbegin(); cit != units.cend(); cit++) {
    dropdown_bank->append(*cit);
  }

  auto drop_down = Gtk::make_managed<Gtk::DropDown>();
  drop_down->set_model(dropdown_bank);
  drop_down->set_show_arrow(true);
  m_Grid.attach(*drop_down, horizontal_position + 7, vertical_position + 1, 1, 1);
}





void MetricsSubsystem::add_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horozontal_position)
{
  auto entry_label = Gtk::make_managed<Gtk::Label>(tab_name);

  m_Grid.attach(*entry_label, horozontal_position++, vertical_position);

  auto entry_number = Gtk::make_managed<Gtk::Entry>();
  entry_number->set_expand(false);
  entry_number->set_input_purpose(Gtk::InputPurpose::NUMBER);
  entry_number->set_max_length(15);
  entry_number->select_region(0, entry_number->get_text_length());

  m_Grid.attach(*entry_number, horozontal_position++, vertical_position);

  auto unit_label = Gtk::make_managed<Gtk::Label>("Unit: ");

  m_Grid.attach(*unit_label, horozontal_position++, vertical_position);

  auto dropdown_bank = Gtk::StringList::create({});

  for (auto cit = units.cbegin(); cit != units.cend(); cit++)
  {
    dropdown_bank->append(*cit);
  }

  auto drop_down = Gtk::make_managed<Gtk::DropDown>();

  drop_down->set_model(dropdown_bank);
  // drop_down->set_selected(1);
  // drop_down->set_expand(false);
  drop_down->set_show_arrow(true);

  m_Grid.attach(*drop_down, horozontal_position++, vertical_position);
  // TODO CONNECT WIDGETS TO SETTERS!
}
