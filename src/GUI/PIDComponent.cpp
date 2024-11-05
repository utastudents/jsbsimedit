#include "PIDComponent.hpp"

namespace JSBEdit{

PIDComponent::PIDComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void PIDComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};