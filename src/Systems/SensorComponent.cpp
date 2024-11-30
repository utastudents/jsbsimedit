#include "SensorComponent.hpp"

namespace DragDrop{

SensorComponent::SensorComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::SENSOR)
{
}

void SensorComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}
    
void SensorComponent::LoadFromXml(JSBEdit::XMLNode& node)
{
    
}

};