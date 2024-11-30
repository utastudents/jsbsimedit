#include "GainComponent.hpp"

namespace DragDrop{

GainComponent::GainComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::GAIN)
{
}

void GainComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
}

void GainComponent::LoadFromXml(JSBEdit::XMLNode& node)
{

}


};