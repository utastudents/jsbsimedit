#include <iostream>
#include "MetricsSubsystem.hpp"
#include "XML/XMLDoc.hpp"
#include "XML/XMLNode.hpp"
#include <gtkmm.h>

MetricsSubsystem::MetricsSubsystem()
{
  m_Name = "Metrics";
  std::map<std::string, Metrics::string_vector> unit_map{
      {"wingarea", {"FT2", "M2"}},
      {"wingspan", {"FT", "M"}},
      {"wing_incidence", {"DEG"}},
      {"chord", {"FT", "M"}},
      {"htailarea", {"FT2", "M2"}},
      {"htailarm", {"FT", "M"}},
      {"vtailarea", {"FT2", "M2"}},
      {"vtailarm", {"FT", "M"}},
      {"location", {"IN", "FT", "M"}}};

  // Create and initialize Metrics::Data_Unit instances
  std::string node_name{""};

  node_name = "wingarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "wingspan";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "chord";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "htailarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "htailarm";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "vtailarea";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "vtailarm";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  node_name = "wing_incidence";
  data_units[node_name] = std::make_unique<Metrics::Data_Unit>(0.0, unit_map[node_name]);

  // Create and initialize Metrics::Vertex_Unit instances
  node_name = "Aerodynamic Reference Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.0, 0.0, 0.0, unit_map["location"]);

  node_name = "Eye Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.0, 0.0, 0.0, unit_map["location"]);

  node_name = "Visual Reference Point";
  vertex_data_units[node_name] = std::make_unique<Metrics::Vertex_Unit>(0.0, 0.0, 0.0, unit_map["location"]);
}

void MetricsSubsystem::Create()
{
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  // Add widgets for data units
  int row = 0;
  for (auto cit = data_units.cbegin(); cit != data_units.cend(); ++cit)
  {
    add_data_unit(cit->first, cit->second->get_its_unit()->get_unit_bank(), row++, 0);
  }

  // Add widgets for vertex data units
  row++; // Add an empty row between data units and vertex data units
  for (auto cit = vertex_data_units.cbegin(); cit != vertex_data_units.cend(); ++cit)
  {
    add_vertex_data_unit(cit->first, cit->second->get_its_unit()->get_unit_bank(), row, 0);
    row += 2;
  }

  auto save_button = Gtk::make_managed<Gtk::Button>();
  save_button->set_label("Save");
  save_button->signal_activate().connect([this]()
                                         { save_data(xmlptr()); });

  m_Grid.attach(*save_button, 0, row);

  // load metrics from XML file
  if (xmlptr())
    load_data(xmlptr());
}

// This method should be invoked when the XML is being saved
void MetricsSubsystem::save_data(JSBEdit::XMLDoc *doc_ptr)
{
  std::cout << "MetricsSubsystem::save_data(JSBEdit::XMLDoc *doc_ptr)\n";

  // // Get metrics node
  // JSBEdit::XMLNode metricsNode = doc_ptr->GetNode("/fdm_config/metrics");
  // if (!metricsNode)
  // {
  //   std::cerr << "Error: <metrics> node not found in XML file." << std::endl;
  //   return;
  // }

  // // Saving data_unit s
  // for (auto cit = data_units.cbegin(); cit != data_units.cend(); ++cit)
  // {

  //   JSBEdit::XMLNode node = metricsNode.FindChild(cit->first);

  //   if (node)
  //   {
  //     AttributeKV unit_attribute{"unit", cit->second->get_its_unit()->get_unit()};
  //     node.SetAttribute(unit_attribute);
  //     node.SetText(std::to_string(cit->second->get_value()));

  //     cit->second->set_value(value);
  //     cit->second->get_its_unit()->set_current_unit(unit);
  //   }
  // }

  // // Save vertex_unit s
  // std::vector<JSBEdit::XMLNode> locationNodes = metricsNode.GetChildren();
  // for (auto &locationNode : locationNodes)
  // {
  //   if (locationNode.GetName() == "location")
  //   {
  //     std::string name = locationNode.GetAttribute("name").second;

  //     if (name == "AERORP")
  //       name = "Aerodynamic Reference Point";

  //     else if (name == "EYEPOINT")
  //       name = "Eye Point";

  //     else if (name == "VRP")
  //       name = "Visual Reference Point";

  //     else
  //       continue;

  //     AttributeKV unit_attribute{"unit", vertex_data_units[name]->get_its_unit()->get_unit()};
  //     node.SetAttribute(unit_attribute);

  //     auto &x_node{locationNode.FindChild("x")};
  //     x_node.SetText(vertex_data_units[name]->get_x());

  //     auto &x_node{locationNode.FindChild("y")};
  //     x_node.SetText(vertex_data_units[name]->get_y());

  //     auto &x_node{locationNode.FindChild("z")};
  //     x_node.SetText(vertex_data_units[name]->get_z());
  //   }
  // }

  // // This is only used for testing. Remove this function so mainwindow can handle the file path
  // doc_ptr->SaveToFile("f16.xml");
}

// This method should be invoked when an XML is opened
void MetricsSubsystem::load_data(JSBEdit::XMLDoc *doc_ptr)
{
  // Get metrics node
  JSBEdit::XMLNode metricsNode = doc_ptr->GetNode("/fdm_config/metrics");
  if (!metricsNode)
  {
    std::cerr << "Error: <metrics> node not found in XML file." << std::endl;
    return;
  }

  for (auto cit = data_units.cbegin(); cit != data_units.cend(); ++cit)
  {

    JSBEdit::XMLNode node = metricsNode.FindChild(cit->first);

    if (node)
    {
      double value = update_text(node.GetText());
      std::string unit = node.GetAttribute("unit").second;

      cit->second->set_value(value);
      cit->second->get_its_unit()->set_current_unit(unit);

      // Searching for widgets to update
      Gtk::Entry *value_box{nullptr};
      Gtk::DropDown *unit_dropdown{nullptr};
      for (int i = 0; i < LABELS; i++)
      {
        auto it = m_Grid.get_child_at(0, i);
        auto *label = dynamic_cast<Gtk::Label *>(it);
        if (label->get_text().raw() == cit->first)
        {
          value_box = dynamic_cast<Gtk::Entry *>(m_Grid.get_child_at(1, i));
          unit_dropdown = dynamic_cast<Gtk::DropDown *>(m_Grid.get_child_at(3, i));
          break;
        }
      }

      if (value_box)
        value_box->set_text(std::to_string(cit->second->get_value()));

      if (unit_dropdown)
        set_selected_by_name(unit_dropdown, unit);
    }
  }

  // Process locations
  std::vector<JSBEdit::XMLNode> locationNodes = metricsNode.GetChildren();
  for (auto &locationNode : locationNodes)
  {
    if (locationNode.GetName() == "location")
    {
      std::string name = locationNode.GetAttribute("name").second;
      std::string unit = locationNode.GetAttribute("unit").second;

      double x = update_text(locationNode.FindChild("x").GetText());
      double y = update_text(locationNode.FindChild("y").GetText());
      double z = update_text(locationNode.FindChild("z").GetText());

      if (name == "AERORP")
        name = "Aerodynamic Reference Point";

      else if (name == "EYEPOINT")
        name = "Eye Point";

      else if (name == "VRP")
        name = "Visual Reference Point";

      else
        continue;

      vertex_data_units[name]->set_vertex(x, y, z);
      vertex_data_units[name]->get_its_unit()->set_current_unit(unit);

      // Searching for widgets to update
      Gtk::Entry *x_box{nullptr};
      Gtk::Entry *y_box{nullptr};
      Gtk::Entry *z_box{nullptr};
      Gtk::DropDown *unit_dropdown{nullptr};
      for (int i = 9; i <= 13; i += 2)
      {
        auto it = m_Grid.get_child_at(0, i);
        auto *label = dynamic_cast<Gtk::Label *>(it);
        if (label->get_text().raw() == name)
        {
          x_box = dynamic_cast<Gtk::Entry *>(m_Grid.get_child_at(1, i + 1));
          y_box = dynamic_cast<Gtk::Entry *>(m_Grid.get_child_at(3, i + 1));
          z_box = dynamic_cast<Gtk::Entry *>(m_Grid.get_child_at(5, i + 1));
          unit_dropdown = dynamic_cast<Gtk::DropDown *>(m_Grid.get_child_at(7, i + 1));
          break;
        }
      }

      if (x_box)
        x_box->set_text(std::to_string(vertex_data_units[name]->get_x()));

      if (y_box)
        y_box->set_text(std::to_string(vertex_data_units[name]->get_y()));

      if (z_box)
        z_box->set_text(std::to_string(vertex_data_units[name]->get_z()));

      if (unit_dropdown)
        set_selected_by_name(unit_dropdown, unit);
    }
  }
}

void MetricsSubsystem::add_vertex_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horizontal_position)
{
  auto section_label = Gtk::make_managed<Gtk::Label>(tab_name);
  m_Grid.attach(*section_label, horizontal_position, vertical_position++, 6, 1);

  std::vector<Gtk::Label *> coordinate_labels{};
  std::vector<Gtk::Entry *> entry_boxes{};

  for (char variable_name = 88; variable_name <= 90; variable_name++)
  {
    coordinate_labels.push_back(Gtk::make_managed<Gtk::Label>(std::string(1, variable_name) + ": "));
    entry_boxes.push_back(Gtk::make_managed<Gtk::Entry>());

    entry_boxes.back()->set_expand(false);
    entry_boxes.back()->set_input_purpose(Gtk::InputPurpose::NUMBER);
    entry_boxes.back()->set_max_length(15);

    m_Grid.attach(*coordinate_labels.back(), horizontal_position++, vertical_position, 1, 1);
    m_Grid.attach(*entry_boxes.back(), horizontal_position++, vertical_position, 1, 1);
  }

  // Linking to X
  auto the_x = entry_boxes.at(0);
  the_x->set_text(std::to_string(vertex_data_units[tab_name]->get_x()));
  the_x->signal_activate().connect([this, the_x, tab_name]()
                                   {
    vertex_data_units[tab_name]->set_x(update_text(the_x->get_text()));
    the_x->set_text(std::to_string(vertex_data_units[tab_name]->get_x())); });

  // Linking to Y
  auto the_y = entry_boxes.at(1);
  the_y->set_text(std::to_string(vertex_data_units[tab_name]->get_z()));
  the_y->signal_activate().connect([this, the_y, tab_name]()
                                   {
    vertex_data_units[tab_name]->set_y(update_text(the_y->get_text()));
    the_y->set_text(std::to_string(vertex_data_units[tab_name]->get_z())); });

  // Linking to Z
  auto the_z = entry_boxes.at(2);
  the_z->set_text(std::to_string(vertex_data_units[tab_name]->get_z()));
  the_z->signal_activate().connect([this, the_z, tab_name]()
                                   {
    vertex_data_units[tab_name]->set_z(update_text(the_z->get_text()));
    the_z->set_text(std::to_string(vertex_data_units[tab_name]->get_z())); });

  // Add the unit dropdown
  auto unit_label = Gtk::make_managed<Gtk::Label>("Unit: ");
  m_Grid.attach(*unit_label, horizontal_position++, vertical_position, 1, 1);

  auto dropdown_bank = Gtk::StringList::create({});
  for (auto cit = units.cbegin(); cit != units.cend(); cit++)
  {
    dropdown_bank->append(*cit);
  }

  auto drop_down = Gtk::make_managed<Gtk::DropDown>();
  drop_down->set_model(dropdown_bank);
  drop_down->set_show_arrow(true);
  m_Grid.attach(*drop_down, horizontal_position++, vertical_position, 1, 1);

  // Connect dropdown signal to a handler
  drop_down->property_selected().signal_changed().connect(
      [this, tab_name, drop_down, dropdown_bank]()
      {
        auto selected = drop_down->get_selected();
        if (selected != -1)
        {
          auto selected_unit = dropdown_bank->get_string(selected);
          vertex_data_units[tab_name]->get_its_unit()->set_current_unit(selected_unit);
        }
      });
}

void MetricsSubsystem::add_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horozontal_position)
{
  auto entry_label = Gtk::make_managed<Gtk::Label>(tab_name);

  m_Grid.attach(*entry_label, horozontal_position++, vertical_position);

  auto entry_number = Gtk::make_managed<Gtk::Entry>();
  entry_number->set_expand(false);
  entry_number->set_input_purpose(Gtk::InputPurpose::NUMBER);
  entry_number->set_text(std::to_string(data_units[tab_name]->get_value()));

  entry_number->signal_activate().connect([this, entry_number, tab_name]()
                                          {
    data_units[tab_name]->set_value(update_text(entry_number->get_text()));
    entry_number->set_text(std::to_string(data_units[tab_name]->get_value())); });

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

  // Connect dropdown signal to a handler
  drop_down->property_selected().signal_changed().connect(
      [this, tab_name, drop_down, dropdown_bank]()
      {
        auto selected = drop_down->get_selected();
        if (selected != -1)
        {
          auto selected_unit = dropdown_bank->get_string(selected);
          data_units[tab_name]->get_its_unit()->set_current_unit(selected_unit);
        }
      });
}

double MetricsSubsystem::update_text(const std::string &data)
{
  try
  {
    return std::stod(data);
  }
  catch (const std::exception &e)
  {
    return 0.0;
  }
}

void MetricsSubsystem::set_selected_by_name(Gtk::DropDown *dropdown, const std::string &name)
{
  auto bank = std::dynamic_pointer_cast<Gtk::StringList>(dropdown->get_model());
  if (bank)
  {
    for (int i = 0; i < bank->get_n_items(); ++i)
    {
      if (bank->get_string(i).raw() == name)
      {
        dropdown->set_selected(i);
      }
    }
  }
}
