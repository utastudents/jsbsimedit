#pragma once

#include <gtkmm.h>
#include "inc/XML_api.hpp"
#include "inc/Subsystem.hpp"
#include "Metrics/Data_Unit.hpp"
#include "Metrics/Vertex_Unit.hpp"

class MetricsSubsystem : public Subsystem
{
  public:
    MetricsSubsystem();

    void Create();

    void load_data(JSBEdit::XMLDoc* doc_ptr);

    void save_data(JSBEdit::XMLDoc* doc_ptr);

    void add_data_unit(std::string tab_name, Metrics::string_vector units, int horozontal_position, int vertical_position); 

    void add_vertex_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horizontal_position);

    static double update_text(const std::string& data);

    static void set_selected_by_name(Gtk::DropDown* dropdown, const std::string& name);

  private:
    static constexpr int LABELS{8};

    std::map<std::string, std::unique_ptr<Metrics::Data_Unit>> data_units;
    std::map<std::string, std::unique_ptr<Metrics::Vertex_Unit>> vertex_data_units;

};
