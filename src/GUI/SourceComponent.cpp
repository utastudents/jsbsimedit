#include "SourceComponent.hpp"

namespace JSBEdit{

SourceComponent::SourceComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void SourceComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};