#include "Data_Unit.hpp"

namespace Metrics
{

Data_Unit::Data_Unit(string_vector& unit_bank) {
    its_unit = std::make_unique<Unit>(unit_bank);
}

Data_Unit::Data_Unit(int _value, string_vector& unit_bank)
    : the_value(_value)
{
    its_unit = std::make_unique<Unit>(unit_bank);
}

void Data_Unit::set_value(double p_value) {
    the_value = p_value;
}

double Data_Unit::get_value() const {
    return the_value;
}

Unit* Data_Unit::get_its_unit(){ return its_unit.get(); }

}