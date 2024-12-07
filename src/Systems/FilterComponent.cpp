#include "FilterComponent.hpp"
#include <gtkmm.h>

namespace DragDrop {

FilterComponent::FilterComponent(const std::string& name)
    : IComponentCommon(name, ComponentType::FILTER), 
      ComponentName(name), 
      Type("Default"), 
      Order(1), 
      MaxValue(0.0f), 
      MinValue(0.0f), 
      IsEnabled(false) {
}

void FilterComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app) {
    // Implement logic for initializing the GUI
}

void FilterComponent::LoadFromXml(JSBEdit::XMLNode& node) {
    // Load component configuration from XML node
}

} // namespace DragDrop