#include "MassBalanceSubsystem.hpp"
#include "Location.hpp"
#include "PointMassDialogue.hpp"
#include "inc/XML_api.hpp"
#include <assert.h>
#include <iostream>
#include <vector>

MassBalanceSubsystem::MassBalanceSubsystem() {
  m_Name = "Mass Balance";
  //std::cout << "In MassBalanceSubsystem constructor" << std::endl;
}

void MassBalanceSubsystem::Create() {
  //std::cout << "In MassBalanceSubsystem::Create" << std::endl;

  // Example code for reading from the xml file.
  // This code may or may not go here, but this was a place
  // to put it.
  //
  //
  assert(xmlptr());
  //std::cout << "---------------------------------------------------------------"
  //             "----------"
  //          << std::endl;
  //std::cout << "This is in mass balance, reading the xml file" << std::endl;
  JSBEdit::XMLNode node = xmlptr()->GetNode("fdm_config/mass_balance");
  JSBEdit::XMLNode locNode =
      xmlptr()->GetNode("fdm_config/mass_balance/location");
  JSBEdit::XMLNode massNode =
      xmlptr()->GetNode("fdm_config/mass_balance/pointmass");
  JSBEdit::XMLNode massLocNode =
      xmlptr()->GetNode("fdm_config/mass_balance/pointmass/location");
  auto a = node.GetAttribute(std::string("negated_crossproduct_inertia"));

  //std::cout << a.first << " -->  " << a.second << std::endl;

  // store this in the class
  m_airplane.negated = a.second == "true";

  //std::cout << "the value is " << m_airplane.negated << std::endl;

  auto children = node.GetChildren();
  auto locChildren = locNode.GetChildren();
  auto massChildren = massNode.GetChildren();
  auto massLocChildren = massLocNode.GetChildren();
  std::cout << "there are " << children.size() << " children " << std::endl;
  for (auto &child : children) {
    std::vector<AttributeKV> attributes = child.GetAttributes();
    //std::cout << child.GetName() << " " << child.GetText();

    if (child.GetName() == "ixx") {
      m_airplane.setIxx(std::stod(child.GetText()));
    } else if (child.GetName() == "iyy") {

      m_airplane.setIyy(std::stod(child.GetText()));

    } else if (child.GetName() == "izz") {
      m_airplane.setIzz(std::stod(child.GetText()));
    } else if (child.GetName() == "ixy") {
      m_airplane.setIxy(std::stod(child.GetText()));
    } else if (child.GetName() == "ixz") {
      m_airplane.setIxz(std::stod(child.GetText()));
    } else if (child.GetName() == "iyz") {
      m_airplane.setIyz(std::stod(child.GetText()));
    } else if (child.GetName() == "emptywt") {
      m_Emptymass.setEmptyMass(std::stod(child.GetText()));
    } else if (child.GetName() == "location") {
      for (auto &locChild : locChildren) {

        if (locChild.GetName() == "x") {

          m_Location.setX(std::stod(locChild.GetText()));
        } else if (locChild.GetName() == "y") {
          m_Location.setY(std::stod(locChild.GetText()));
        } else if (locChild.GetName() == "z") {
          m_Location.setZ(std::stod(locChild.GetText()));
        }
      }
    } else if (child.GetName() == "pointmass") {
      for (auto &massChild : massChildren) {
        if (massChild.GetName() == "weight") {
          m_Pointmass.setWeight(std::stod(massChild.GetText()));
        } else if (massChild.GetName() == "location") {
          for (auto &massLocChild : massLocChildren) {
            if (massLocChild.GetName() == "x") {
              m_Pointmass.setX(std::stod(massLocChild.GetText()));
            } else if (massLocChild.GetName() == "y") {
              m_Pointmass.setY(std::stod(massLocChild.GetText()));
            } else if (massLocChild.GetName() == "z") {
              m_Pointmass.setZ(std::stod(massLocChild.GetText()));
            }
          }
        }
      }

      // If there are units, deal with them here
    }
    if (attributes[0].first == "unit" && attributes[0].second == "SLUG*FT2") {
      m_airplane.setUnit(attributes[0].second);
    } else if (attributes[0].first == "unit" && attributes[0].second == "LBS") {
      m_Emptymass.setUnits(attributes[0].second);
    } else if (attributes[0].first == "name") {
      m_Pointmass.setName(attributes[0].second);
    }

    //std::cout << std::endl;
  }
  //std::cout << m_airplane.getUnit() << " " << m_Emptymass.getUnits() << " "
  //          << m_Location.getUnits() << " " << m_Pointmass.getName();
  //std::cout << "---------------------------------------------------------------"
  //             "----------"
  //          << std::endl;
//
//
//
//
//
#ifdef THIS_IS_AN_EXAMPLE_FROM_THE_XML_FILE
  <mass_balance negated_crossproduct_inertia = "true"> < ixx unit =
      "SLUG*FT2" > 9496 < / ixx > < iyy unit =
          "SLUG*FT2" > 55814 < / iyy > < izz unit =
              "SLUG*FT2" > 63100 < / izz > < ixy unit =
                  "SLUG*FT2" > 0 < / ixy > <ixz unit = "SLUG*FT2"> - 982 <
                  / ixz > < iyz unit =
                      "SLUG*FT2" > 0 < / iyz > < emptywt unit =
                          "LBS" > 17400 < / emptywt >
                          <location name = "CG" unit = "IN"><x> - 193 < / x > <
                          y > 0 < / y > <z> - 5.1 < / z > </ location>
                          <pointmass name = "Pilot"> < weight unit =
                              "LBS" > 230 < / weight >
                              <location name = "POINTMASS" unit = "IN">
                                  <x> - 336.2 <
                              / x > < y > 0 < / y > < z > 0 < / z >
                              </ location></ pointmass></ mass_balance>
#endif
                                  // end Example Code

                                  // test values for empty mass

                                  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);
  m_Grid.set_margin(10);

  // empty weight label
  auto label_empty_weight = Gtk::make_managed<Gtk::Label>("Empty Weight(*)");
  m_Grid.attach(*label_empty_weight, 0, 0);

  // box to view weight
  auto entry_empty_weight = Gtk::make_managed<Gtk::Entry>();
  entry_empty_weight->set_editable(true);
  m_Grid.attach(*entry_empty_weight, 1, 0);
  entry_empty_weight->set_text(std::to_string(m_Emptymass.getEmptyMass()));

  entry_empty_weight->signal_activate().connect([entry_empty_weight, this]() {
    double new_empty_mass = std::stod(entry_empty_weight->get_text());
    m_Emptymass.setEmptyMass(new_empty_mass);
    entry_empty_weight->set_text(std::to_string(m_Emptymass.getEmptyMass()));
  });

  // dropdown to choose lbs or kg for empty mass
  auto combo_units = Gtk::make_managed<Gtk::ComboBoxText>();
  combo_units->append("lbs");
  combo_units->append("kgs");
  combo_units->set_active(0); // default to "lbs"
  m_Grid.attach(*combo_units, 2, 0);

  // signal handler for empty mass dropdown
  combo_units->signal_changed().connect(
      [this, entry_empty_weight, combo_units]() {
        std::string selected_unit = combo_units->get_active_text();
        if ((selected_unit == "kgs" && m_Emptymass.getUnits() == "LBS") ||
            (selected_unit == "lbs" && m_Emptymass.getUnits() == "KGS")) {
          m_Emptymass.convertUnits(); // convert units
          entry_empty_weight->set_text(
              std::to_string(m_Emptymass.getEmptyMass())); // update display
        }
      });

  // location label
  auto label_location = Gtk::make_managed<Gtk::Label>("Location(*)");
  m_Grid.attach(*label_location, 0, 3);

  // x coord label
  auto label_x = Gtk::make_managed<Gtk::Label>("x=");
  m_Grid.attach(*label_x, 0, 4);

  // x box
  auto entry_x = Gtk::make_managed<Gtk::Entry>();
  entry_x->set_editable(false);
  m_Grid.attach(*entry_x, 1, 4);
  entry_x->set_text(std::to_string(m_Location.getX()));

  // y coord label
  auto label_y = Gtk::make_managed<Gtk::Label>("y=");
  m_Grid.attach(*label_y, 2, 4);

  // y box
  auto entry_y = Gtk::make_managed<Gtk::Entry>();
  entry_x->set_editable(false);
  m_Grid.attach(*entry_y, 3, 4);
  entry_y->set_text(std::to_string(m_Location.getY()));

  // z coord label
  auto label_z = Gtk::make_managed<Gtk::Label>("z=");
  m_Grid.attach(*label_z, 4, 4);

  // z box
  auto entry_z = Gtk::make_managed<Gtk::Entry>();
  entry_x->set_editable(false);
  m_Grid.attach(*entry_z, 5, 4);
  entry_z->set_text(std::to_string(m_Location.getZ()));

  // location units dropdown
  auto combo_loc_units = Gtk::make_managed<Gtk::ComboBoxText>();
  combo_loc_units->append("in");
  combo_loc_units->append("cm");
  combo_loc_units->set_active(0); // Default to "in"
  m_Grid.attach(*combo_loc_units, 6, 4);

  // signal handler for length units dropdown
  combo_loc_units->signal_changed().connect(
      [this, entry_x, entry_y, entry_z, combo_loc_units]() {
        std::string selected_unit = combo_loc_units->get_active_text();
        if ((selected_unit == "cm" && m_Location.getUnits() == "in") ||
            (selected_unit == "in" && m_Location.getUnits() == "cm")) {
          m_Location.convertLengthUnits();
          entry_x->set_text(std::to_string(m_Location.getX()));
          entry_y->set_text(std::to_string(m_Location.getY()));
          entry_z->set_text(std::to_string(m_Location.getZ()));
        }
      });

  // moment of inertia label
  auto label_moment_inertia =
      Gtk::make_managed<Gtk::Label>("Moment of inertia (*)");
  m_Grid.attach(*label_moment_inertia, 0, 5);

  // Ixx
  auto inertia_label_Ixx = Gtk::make_managed<Gtk::Label>("Ixx = ");
  m_Grid.attach(*inertia_label_Ixx, 0, 6);

  auto entry_inertia_Ixx = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Ixx->set_editable(false);
  entry_inertia_Ixx->set_text(std::to_string(m_airplane.getIxx()));
  m_Grid.attach(*entry_inertia_Ixx, 1, 6);

  // Iyy
  auto inertia_label_Iyy = Gtk::make_managed<Gtk::Label>("Iyy = ");
  m_Grid.attach(*inertia_label_Iyy, 0, 7);

  auto entry_inertia_Iyy = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Iyy->set_editable(false);
  entry_inertia_Iyy->set_text(std::to_string(m_airplane.getIyy()));
  m_Grid.attach(*entry_inertia_Iyy, 1, 7);

  // Izz
  auto inertia_label_Izz = Gtk::make_managed<Gtk::Label>("Izz = ");
  m_Grid.attach(*inertia_label_Izz, 0, 8);

  auto entry_inertia_Izz = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Izz->set_editable(false);
  entry_inertia_Izz->set_text(std::to_string(m_airplane.getIzz()));
  m_Grid.attach(*entry_inertia_Izz, 1, 8);

  // Ixz
  auto inertia_label_Ixz = Gtk::make_managed<Gtk::Label>("Ixz = ");
  m_Grid.attach(*inertia_label_Ixz, 3, 6);

  auto entry_inertia_Ixz = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Ixz->set_editable(false);
  entry_inertia_Ixz->set_text(std::to_string(m_airplane.getIxz()));
  m_Grid.attach(*entry_inertia_Ixz, 4, 6);

  // Iyz
  auto inertia_label_Iyz = Gtk::make_managed<Gtk::Label>("Iyz = ");
  m_Grid.attach(*inertia_label_Iyz, 3, 7);

  auto entry_inertia_Iyz = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Iyz->set_editable(false);
  entry_inertia_Iyz->set_text(std::to_string(m_airplane.getIyz()));
  m_Grid.attach(*entry_inertia_Iyz, 4, 7);

  // Ixy
  auto inertia_label_Ixy = Gtk::make_managed<Gtk::Label>("Ixy = ");
  m_Grid.attach(*inertia_label_Ixy, 3, 8);

  auto entry_inertia_Ixy = Gtk::make_managed<Gtk::Entry>();
  entry_inertia_Ixy->set_editable(false);
  entry_inertia_Ixy->set_text(std::to_string(m_airplane.getIxy()));
  m_Grid.attach(*entry_inertia_Ixy, 4, 8);

  // Dropdown for units
  auto combo_inertia_units = Gtk::make_managed<Gtk::ComboBoxText>();
  combo_inertia_units->append("SLUG*FT2");
  combo_inertia_units->append("KG*M2");
  combo_inertia_units->set_active(0); // Default to "SLUG*FT2"
  m_Grid.attach(*combo_inertia_units, 5, 6);

  combo_inertia_units->signal_changed().connect(
      [this, entry_inertia_Ixx, entry_inertia_Iyy, entry_inertia_Izz,
       entry_inertia_Ixz, entry_inertia_Iyz, entry_inertia_Ixy,
       combo_inertia_units]() {
        std::string selected_unit = combo_inertia_units->get_active_text();

        // Perform unit conversion if necessary
        if (selected_unit != m_airplane.getUnit()) {
          m_airplane.convertInertiaUnits();
          entry_inertia_Ixx->set_text(std::to_string(m_airplane.getIxx()));
          entry_inertia_Iyy->set_text(std::to_string(m_airplane.getIyy()));
          entry_inertia_Izz->set_text(std::to_string(m_airplane.getIzz()));
          entry_inertia_Ixz->set_text(std::to_string(m_airplane.getIxy()));
          entry_inertia_Iyz->set_text(std::to_string(m_airplane.getIxz()));
          entry_inertia_Ixy->set_text(std::to_string(m_airplane.getIyz()));
        }
      });

  // point mass label
  auto label_point_mass = Gtk::make_managed<Gtk::Label>("Point mass");
  m_Grid.attach(*label_point_mass, 0, 9);

  // entry point mass
  std::ostringstream oss;
  oss << "Name: " << m_Pointmass.getName()
      << "\tWeight: " << m_Pointmass.getWeight() << " "
      << m_Pointmass.getWeightUnit()
      << "\t Location: \t x= " << m_Pointmass.getX()
      << "\ty= " << m_Pointmass.getY() << "\tz= " << m_Pointmass.getZ() << " "
      << m_Pointmass.getLocationUnit();
  auto entry_point_mass = Gtk::make_managed<Gtk::Entry>();
  entry_point_mass->set_editable(false);
  entry_point_mass->set_vexpand(true);
  entry_point_mass->set_text(oss.str());
  m_Grid.attach(*entry_point_mass, 0, 10, 8, 4);

  // button to add a new point mass
  auto button_new_mass = Gtk::make_managed<Gtk::Button>("Add a new point mass");
  m_Grid.attach(*button_new_mass, 0, 14, 4, 1);
  button_new_mass->signal_clicked().connect(
      sigc::mem_fun(*this, &MassBalanceSubsystem::on_button_pressed));

  // button to delete selected point mass
  auto button_del_mass =
      Gtk::make_managed<Gtk::Button>("Delete the selected point mass");
  m_Grid.attach(*button_del_mass, 4, 14, 4, 1);
}

void MassBalanceSubsystem::on_button_pressed() {
  auto point_mass_dialogue = new PointMassDialogue();

  point_mass_dialogue->show();
}
