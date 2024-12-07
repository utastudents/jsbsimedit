#include "Vertex_Unit.hpp"

namespace Metrics
{

Vertex_Unit::Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank)
    : x(p_x), y(p_y), z(p_z)
{
    its_unit = std::make_unique<Unit>(unit_bank);
}

Unit* Vertex_Unit::get_its_unit() { return its_unit.get(); }

void Vertex_Unit::set_x(double data) { x = data; }

void Vertex_Unit::set_y(double data) { y = data; }

void Vertex_Unit::set_z(double data) { z = data; }

void Metrics::Vertex_Unit::set_vertex(double p_x, double p_y, double p_z) {
    x = p_x;
    y = p_y;
    z = p_z;
}

double Vertex_Unit::get_x() const { return x; }
double Vertex_Unit::get_y() const { return y; }
double Vertex_Unit::get_z() const { return z; }

}