#include "DeadbandComponent.hpp"

namespace DragDrop{

// Constructor
DeadbandComponent::DeadbandComponent(const std::string& name)
    : IComponentCommon(name, ComponentType::DEADBAND)
{
}

void DeadbandComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
}

};
