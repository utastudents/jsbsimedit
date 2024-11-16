#include "DestinationComponent.hpp"

namespace DragDrop{

DestinationComponent::DestinationComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::DESTINATION)
{
}

void DestinationComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};