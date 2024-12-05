#include "SwitchComponent.hpp"

namespace DragDrop {

// Constructor
SwitchComponent::SwitchComponent(const std::string& name)
    : IComponentCommon(name, ComponentType::SWITCH) {}

void SwitchComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app) {
    // To be implemented, similar to the Deadband structure
}

void SwitchComponent::LoadFromXml(JSBEdit::XMLNode& node) {
    // XML loading logic for:
    // Description, IsClipperEnabled, MinClip, MaxClip, Inputs, InputPolarity, OutputConfig
}

}