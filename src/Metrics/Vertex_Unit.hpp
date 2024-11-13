#pragma once

#include "Unit.hpp"

namespace Metrics
{
    class Vertex_Unit{
    public:
        Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank);
        ~Vertex_Unit() = default;  // Virtual destructor
        void set_x(double p_x);
        void set_y(double p_y);
        void set_z(double p_z);
        double get_x() const;
        double get_y() const;
        double get_z() const;
        Unit* get_its_unit();

    private:
        std::unique_ptr<Unit> its_unit;
        double x{ 0 }, y{ 0 }, z{ 0 };
    };
}
