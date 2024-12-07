#include "SummerComponent.hpp"

namespace DragDrop{

SummerComponent::SummerComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::SUMMER)
{
}

void SummerComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{}

void SummerComponent::LoadFromXml(JSBEdit::XMLNode& node)
{}
};