#include "SourceComponent.hpp"

SourceComponent::SourceComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void SourceComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}