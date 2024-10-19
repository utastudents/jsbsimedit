#include "vector"
#include "string"
#include "memory"
#include "map"
#include <iostream>

using namespace std;

class Metrics
{
public:
    using string_vector = std::vector<std::string>;

    // Constructor
    Metrics() {
        init(); // Call the init function during construction
    }

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

    class Data_Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Data_Unit(string_vector &unit_bank)
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

    class Positive_Double : public Data_Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Positive_Double(double p_value, string_vector unit_bank) : Data_Unit(unit_bank)
        {
            set_value(p_value);
            its_unit = std::make_unique<Unit>(unit_bank);
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

    class Norm_Double : public Data_Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Norm_Double(double p_value, string_vector unit_bank) : Data_Unit(unit_bank)
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

    class Vertex_Unit: public Data_Unit
    {
    public:
        ////////////////////////////////////////////////////////
        // ------ Constructor ------
        Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank) : Data_Unit(unit_bank), x(p_x), y(p_y), z(p_z)
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
        double get_x()
        {
            return x;
        }
        double get_y()
        {
            return y;
        }
        double get_z()
        {
            return z;
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

    std::map<std::string, std::unique_ptr<Vertex_Unit>> vertex_data_units{}; // 3 of these

    void init() {
        // Initialize the unit bank
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
};

int main() {
    // Create a Metrics instance to ensure everything compiles and runs
    Metrics metrics_system;

    return 0; // Indicate successful execution
}
