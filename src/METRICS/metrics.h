#include "vector"
#include "string"
#include "memory"

namespace metrics
{
    using string_vector = std::vector<std::string>;

    class Unit
    {
    public:
        Unit(string_vector &p_bank)
        {
            // Improve copying
            unit_bank = p_bank;
        }
        string_vector &get_unit_bank()
        {
            return unit_bank;
        }
        std::string get_curret_unit()
        {
            return current_unit;
        }
        void set_current_unit(std::string p_unit)
        {
            // Check if unit is in unit bank
            current_unit = p_unit;
        }

    private:
        string_vector unit_bank{};
        std::string current_unit{};
    };

    class My_Data
    {
    public:
        void set_value(double p_value);
        double get_value()
        {
            return the_value;
        }

    protected:
        std::unique_ptr<Unit> its_unit{nullptr};
        double the_value{0};
    };

    class Positive_Double : public My_Data
    {
    public:
        // Constructor
        Positive_Double(double p_value)
        {
            set_value(p_value);
            its_unit = std::make_unique<Unit>();
        }

        void set_value(double p_value)
        {
            if (p_value > 0)
                the_value = p_value;

            else
            {
                // Throw error
            }
        }
    };

    class Norm_Double : public My_Data
    {
    public:
        // Constructor
        Norm_Double(double p_value)
        {
            set_value(p_value);
        }

        void set_value(double p_value)
        {
            the_value = p_value;
        }
    };

}