#include "vector"
#include "string"
#include "memory"
#include "map"

class Metrics
{
public:
    using string_vector = std::vector<std::string>;

private:
    ////////////////////////////////////////////////////////
    // ------ Custom types ------
    ////////////////////////////////////////////////////////

    class Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Unit(string_vector &p_bank)
        {
            // TODO Improve copying
            unit_bank = p_bank;
        }

        ////////////////////////////////////////////////////////
        // ------ Methods ------

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
        ////////////////////////////////////////////////////////
        // ------ Fields ------

        string_vector unit_bank{};

        std::string current_unit{};
    };

    ////////////////////////////////////////////////////////

    class My_Data
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        My_Data(string_vector &unit_bank)
        {
            // TODO check this too
            its_unit = std::make_unique<Unit>(unit_bank);
        }

        ////////////////////////////////////////////////////////
        // ------ Methods ------

        void set_value(double p_value);

        double get_value()
        {
            return the_value;
        }

    protected:
        ////////////////////////////////////////////////////////
        // ------ Fields ------

        std::unique_ptr<Unit> its_unit{nullptr};

        double the_value{0};
    };

    ////////////////////////////////////////////////////////

    class Positive_Double : public My_Data
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Positive_Double(double p_value, string_vector unit_bank) : My_Data(unit_bank)
        {
            set_value(p_value);
            its_unit = std::make_unique<Unit>();
        }

        ////////////////////////////////////////////////////////
        // ------ Methods ------

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

    ////////////////////////////////////////////////////////

    class Norm_Double : public My_Data
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Norm_Double(double p_value, string_vector unit_bank) : My_Data(unit_bank)
        {
            set_value(p_value);
        }

        ////////////////////////////////////////////////////////
        // ------ Methods ------

        void set_value(double p_value)
        {
            the_value = p_value;
        }
    };

    ////////////////////////////////////////////////////////

    class Vertex_Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Vertex_Unit(double p_x, double p_y, double p_z) : x(p_x), y(p_y), z(p_z)
        {
            // Construct Unit instance
        }

        ////////////////////////////////////////////////////////
        // ------ Methods ------

        // Setters
        void set_x(double p_x)
        {
            x = p_x;
        }
        void set_y(double p_y)
        {
            y = p_y;
        }
        void set_z(double p_z)
        {
            z = p_z;
        }

        // Getters
        double get_x(double p_x)
        {
            return p_x;
        }
        double get_y(double p_y)
        {
            return p_y;
        }
        double get_z(double p_z)
        {
            return p_z;
        }

    private:
        ////////////////////////////////////////////////////////
        // ------ Fields ------

        double x{0}, y{0}, z{0};

        std::unique_ptr<Unit> its_unit{nullptr};
    };

    ////////////////////////////////////////////////////////
    // ------ Fields ------

    std::map<std::string, std::unique_ptr<Positive_Double>> positive_data_unit{}; // 7 of these

    std::map<std::string, std::unique_ptr<Norm_Double>> normal_data_units{}; // 1 of these

    std::map<std::string, std::unique_ptr<Vertex_Unit>> normal_data_units{}; // 3 of these
};