#include "SummerComponent.hpp"

namespace DragDrop{

SummerComponent::SummerComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void SummerComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};