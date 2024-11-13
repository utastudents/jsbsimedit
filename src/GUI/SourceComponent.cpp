#include "SourceComponent.hpp"

namespace DragDrop{

SourceComponent::SourceComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void SourceComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};