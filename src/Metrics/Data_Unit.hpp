#pragma once

#include "Unit.hpp"

namespace Metrics
{
    class Data_Unit {
    public:
        Data_Unit(string_vector& unit_bank);
        Data_Unit(int _value, string_vector& unit_bank);
        virtual ~Data_Unit() = default;  // Virtual destructor
        void set_value(double p_value);
        double get_value() const;
        Unit* get_its_unit();

    protected:
        std::unique_ptr<Unit> its_unit;
        double the_value{ 0 };
    };
}