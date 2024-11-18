#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Metrics
{
    using string_vector = std::vector<std::string>;

    class Unit {
    public:
        Unit(string_vector& p_bank);
        string_vector& get_unit_bank();
        std::string get_current_unit();
        void set_current_unit(const std::string& p_unit);

    private:
        string_vector unit_bank;
        std::string current_unit;
    };
}