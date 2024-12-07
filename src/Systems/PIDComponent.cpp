#include "PIDComponent.hpp"

namespace DragDrop{

PIDComponent::PIDComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::PID)
{
}

void PIDComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{}

void PIDComponent::LoadFromXml(JSBEdit::XMLNode& node)
{}


};