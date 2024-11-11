#include "DestinationComponent.hpp"

namespace JSBEdit{

DestinationComponent::DestinationComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void DestinationComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};