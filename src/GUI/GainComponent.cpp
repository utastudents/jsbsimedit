#include "GainComponent.hpp"

namespace JSBEdit{

GainComponent::GainComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void GainComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};