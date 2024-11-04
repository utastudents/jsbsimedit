#include "KinematicsComponent.hpp"

namespace JSBEdit{

KinematicsComponent::KinematicsComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type), table(40)
{
}

void KinematicsComponent::LoadGUI(Glib::RefPtr<Gtk::Box> &uiBox)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
}

};