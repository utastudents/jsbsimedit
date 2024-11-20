#include "Unit.hpp"

namespace Metrics
{

Unit::Unit(string_vector& p_bank)
    : unit_bank(p_bank), current_unit((p_bank.empty()) ? "" : *p_bank.begin()) {}

string_vector& Unit::get_unit_bank() {
    return unit_bank;
}

std::string Unit::get_current_unit() {
    return current_unit;
}

void Unit::set_current_unit(const std::string& p_unit) {
    current_unit = p_unit;
}

}