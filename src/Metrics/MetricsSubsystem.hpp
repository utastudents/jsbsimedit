#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"

#include "Metrics/MetricsSubsystem.hpp"
#include "Metrics/Data_Unit.hpp"
#include "Metrics/Vertex_Unit.hpp"
#include "XML/XMLDoc.hpp"

class MetricsSubsystem : public Subsystem
{
  public:
    MetricsSubsystem();

    void Create();

    void loadMetricsFromXML(const std::string& filepath);

    void add_data_unit(std::string tab_name, Metrics::string_vector units, int horozontal_position, int vertical_position); 

    void add_vertex_data_unit(std::string tab_name, Metrics::string_vector units, int vertical_position, int horizontal_position);

    static double update_text(std::string data);

  private:
    std::map<std::string, std::unique_ptr<Metrics::Data_Unit>> data_units;
    std::map<std::string, std::unique_ptr<Metrics::Vertex_Unit>> vertex_data_units;

};
