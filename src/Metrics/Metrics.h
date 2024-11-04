#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

class Metrics {
public:
    using string_vector = std::vector<std::string>;

    // Constructor
    Metrics();

private:
    ////////////////////////////////////////////////////////
    // ------ Custom types ------
    ////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////

    class Data_Unit {
    public:
        Data_Unit(string_vector& unit_bank);
        virtual ~Data_Unit() = default;  // Virtual destructor
        virtual void set_value(double p_value) = 0;
        double get_value() const;

    protected:
        std::unique_ptr<Unit> its_unit;
        double the_value{ 0 };
    };

    ////////////////////////////////////////////////////////

    class Positive_Double : public Data_Unit {
    public:
        Positive_Double(double p_value, string_vector unit_bank);
        ~Positive_Double() override = default;  // Virtual destructor
        void set_value(double p_value) override;
    };

    ////////////////////////////////////////////////////////

    class Norm_Double : public Data_Unit {
    public:
        Norm_Double(double p_value, string_vector unit_bank);
        ~Norm_Double() override = default;  // Virtual destructor
        void set_value(double p_value) override;
    };

    ////////////////////////////////////////////////////////

    class Vertex_Unit : public Data_Unit {
    public:
        Vertex_Unit(double p_x, double p_y, double p_z, string_vector unit_bank);
        ~Vertex_Unit() override = default;  // Virtual destructor
        void set_x(double p_x);
        void set_y(double p_y);
        void set_z(double p_z);
        double get_x() const;
        double get_y() const;
        double get_z() const;

        void set_value(double p_value) override {
            the_value = p_value;
        }

    private:
        double x{ 0 }, y{ 0 }, z{ 0 };
    };

    ////////////////////////////////////////////////////////
    // ------ Fields ------
    ////////////////////////////////////////////////////////

    std::map<std::string, std::unique_ptr<Positive_Double>> positive_data_unit;
    std::map<std::string, std::unique_ptr<Norm_Double>> normal_data_units;
    std::map<std::string, std::unique_ptr<Vertex_Unit>> vertex_data_units;

    // Initialization function
    void init();
};