#include <Metrics/Metrics.h>
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

// Positive_Double class methods
Metrics::Positive_Double::Positive_Double(double p_value, string_vector unit_bank)
    : Data_Unit(unit_bank) {
    set_value(p_value);
}

void Metrics::Positive_Double::set_value(double p_value) {
    if (p_value > 0)
        the_value = p_value;
}

// Norm_Double class methods
Metrics::Norm_Double::Norm_Double(double p_value, string_vector unit_bank)
    : Data_Unit(unit_bank) {
    set_value(p_value);
}

void Metrics::Norm_Double::set_value(double p_value) {
    the_value = p_value;
}

// Vertex_Unit class methods
Metrics::Vertex_Unit::Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank)
    : Data_Unit(unit_bank), x(p_x), y(p_y), z(p_z) {}

void Metrics::Vertex_Unit::set_x(double p_x) { x = p_x; }
void Metrics::Vertex_Unit::set_y(double p_y) { y = p_y; }
void Metrics::Vertex_Unit::set_z(double p_z) { z = p_z; }

double Metrics::Vertex_Unit::get_x() const { return x; }
double Metrics::Vertex_Unit::get_y() const { return y; }
double Metrics::Vertex_Unit::get_z() const { return z; }

// Metrics init() method
void Metrics::init() {
    string_vector unit_bank = {"FT2", "M2", "FT", "M", "Deg", "In"};

    // Add Positive_Double instances
    positive_data_unit["Wingarea"] = std::make_unique<Positive_Double>(75.0, unit_bank);
    positive_data_unit["Wingspan"] = std::make_unique<Positive_Double>(76.0, unit_bank);
    positive_data_unit["Chord"] = std::make_unique<Positive_Double>(77.0, unit_bank);
    positive_data_unit["Htailarea"] = std::make_unique<Positive_Double>(78.0, unit_bank);
    positive_data_unit["Htailarm"] = std::make_unique<Positive_Double>(79.0, unit_bank);
    positive_data_unit["Vtailarea"] = std::make_unique<Positive_Double>(80.0, unit_bank);
    positive_data_unit["Vtailarm"] = std::make_unique<Positive_Double>(81.0, unit_bank);

    // Add Norm_Double instance
    normal_data_units["Wing Incidence"] = std::make_unique<Norm_Double>(37.0, unit_bank);

    // Add Vertex_Unit instances
    vertex_data_units["Aerodynamic Reference Point"] = std::make_unique<Vertex_Unit>(0.1, 0.2, 0.3, unit_bank);
    vertex_data_units["Eye Point"] = std::make_unique<Vertex_Unit>(0.4, 0.5, 0.6, unit_bank);
    vertex_data_units["Visual Reference Point"] = std::make_unique<Vertex_Unit>(0.7, 0.8, 0.9, unit_bank);
}

int main(int argc, char* argv[]) {
    Metrics metrics_system;
    return 0;
}
