#include "KinematicsComponent.hpp"

namespace DragDrop{

KinematicsComponent::KinematicsComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::KINEMATIC), table(40)
{
}

void KinematicsComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};