#include "KinematicsComponent.hpp"

namespace DragDrop{

KinematicsComponent::KinematicsComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::KINEMATIC)//, table(42)
{
}

void KinematicsComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{}
};