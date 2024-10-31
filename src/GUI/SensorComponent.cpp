#include "SensorComponent.hpp"

namespace JSBEdit{

SensorComponent::SensorComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void SensorComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};