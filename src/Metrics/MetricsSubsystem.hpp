#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"

#include "Metrics/MetricsSubsystem.hpp"
#include "Metrics/Metrics.h"

class MetricsSubsystem : public Subsystem
{
  public:
    std::string m_name;
    MetricsSubsystem(std::string N);
    void Create(); 
    Metrics m_metrics; // not sure if this is good for anything, but it is the class
                       // currently defined for this group.
};
