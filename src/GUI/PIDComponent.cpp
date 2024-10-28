#include "PIDComponent.hpp"

PIDComponent::PIDComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void PIDComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}
