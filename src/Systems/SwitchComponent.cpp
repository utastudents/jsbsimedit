#include "SwitchComponent.hpp"

namespace DragDrop{

// Constructor
SwitchComponent::SwitchComponent(const std::string& name)
    : IComponentCommon(name, ComponentType::SWITCH)
{
}

void SwitchComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
}

void SwitchComponent::LoadFromXml(JSBEdit::XMLNode &node)
{
}
};
