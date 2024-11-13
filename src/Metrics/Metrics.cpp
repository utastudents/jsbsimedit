#include "Metrics.hpp"
#include <iostream>

// Constructor
Metrics::Metrics() {
    init();
}

// Unit class methods
Metrics::Unit::Unit(string_vector& p_bank) : unit_bank(p_bank) {}

Metrics::string_vector& Metrics::Unit::get_unit_bank() {
    return unit_bank;
}

std::string Metrics::Unit::get_current_unit() {
    return current_unit;
}

void Metrics::Unit::set_current_unit(const std::string& p_unit) {
    current_unit = p_unit;
}

// Data_Unit class methods
Metrics::Data_Unit::Data_Unit(string_vector& unit_bank) {
    its_unit = std::make_unique<Unit>(unit_bank);
}

double Metrics::Data_Unit::get_value() const {
    return the_value;
}

Metrics::Unit* Metrics::Data_Unit::get_its_unit(){ return its_unit.get(); }

// Positive_Double class methods
Metrics::Positive_Double::Positive_Double(double p_value, string_vector unit_bank)
    : Data_Unit(unit_bank) {
    the_value = p_value;  // Initialize to 0, actual value set outside
}

void Metrics::Positive_Double::set_value(double p_value) {
    if (p_value > 0)
        the_value = p_value;
}

// Norm_Double class methods
Metrics::Norm_Double::Norm_Double(double p_value, string_vector unit_bank)
    : Data_Unit(unit_bank) {
    the_value = p_value;  // Initialize to 0, actual value set outside
}

void Metrics::Norm_Double::set_value(double p_value) {
    the_value = p_value;
}

// Vertex_Unit class methods
Metrics::Vertex_Unit::Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank)
    : x(p_x), y(p_y), z(p_z)
{
    its_unit = std::make_unique<Unit>(unit_bank);
}

Metrics::Unit* Metrics::Vertex_Unit::get_its_unit() { return its_unit.get(); }

void Metrics::Vertex_Unit::set_x(double p_x) { x = p_x; }
void Metrics::Vertex_Unit::set_y(double p_y) { y = p_y; }
void Metrics::Vertex_Unit::set_z(double p_z) { z = p_z; }

double Metrics::Vertex_Unit::get_x() const { return x; }
double Metrics::Vertex_Unit::get_y() const { return y; }
double Metrics::Vertex_Unit::get_z() const { return z; }

void Metrics::activate() {
	std::cout << "calling Metrics::activate" << std::endl;
}

// Metrics init() method
void Metrics::init() {
    std::cout << "Metrics::init() has been called" << std::endl;

    std::map<std::string, string_vector> unit_map{
        {"wingarea", {"FT2", "M2"}},
        {"wingspan", {"FT", "M"}},
        {"wing_incidence", {"FT", "M"}},
        {"chord", {"DEG"}},
        {"htailarea", {"FT2", "M2"}},
        {"htailarm", {"FT", "M"}},
        {"vtailarea", {"FT2", "M2"}},
        {"vtailarm", {"FT", "M"}},
        {"location", {"IN", "FT", "M"}}};

    // Create and initialize Positive_Double instances
    std::string node_name{""};

    node_name = "wingarea";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "wingspan";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(76.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "chord";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "htailarea";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "htailarm";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "vtailarea";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "vtailarm";
    positive_data_unit[node_name] = std::make_unique<Positive_Double>(0.0, unit_map[node_name]);
    positive_data_unit[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    positive_data_unit[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO positive_data_unit[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    // Create and initialize Norm_Double instance
    node_name = "wing_incidence";
    normal_data_units[node_name] = std::make_unique<Norm_Double>(0.0, unit_map[node_name]);
    normal_data_units[node_name]->set_value(75.0); // TODO GET INFO FROM XML. IF NODE NOT FOUND, SET TO 0
    normal_data_units[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO normal_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    // Create and initialize Vertex_Unit instances
    node_name = "AERORP";
    vertex_data_units[node_name] =
        std::make_unique<Vertex_Unit>(0.1, 0.2, 0.3, unit_map["location"]); // TODO Update from hardcoded values
                                                                            // to info grabbed from xml
    vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "EYEPOINT";
    vertex_data_units["node_name"] =
        std::make_unique<Vertex_Unit>(0.4, 0.5, 0.6, unit_map["location"]); // TODO Update from hardcoded values
                                                                            // to info grabbed from xml
    vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

    node_name = "VRP";
    vertex_data_units[node_name] =
        std::make_unique<Vertex_Unit>(0.7, 0.8, 0.9, unit_map["location"]); // TODO Update from hardcoded values
                                                                            // to info grabbed from xml
    vertex_data_units[node_name]->get_its_unit()->set_current_unit("");
    // TODO SET TO vertex_data_units[node_name]->get_its_unit()->get_unit_bank()[0] if no unit can be found in XML.
    // Otherwise read in current unit from XML and use that if it is valid.

}

