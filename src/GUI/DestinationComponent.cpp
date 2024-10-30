#include "DestinationComponent.hpp"

DestinationComponent::DestinationComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void DestinationComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}