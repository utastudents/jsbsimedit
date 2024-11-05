#include "IComponentCommon.hpp"

namespace JSBEdit{

IComponentCommon::IComponentCommon(const std::string &compName, ComponentType& type)
    : m_componentName(compName), m_componentType(type)
{
}

std::string IComponentCommon::GetName() const
{
    return m_componentName;
}

ComponentType IComponentCommon::GetComponentType() const
{
    return m_componentType;
}

void IComponentCommon::SetName(const std::string &newName)
{
    m_componentName = newName;
}

Glib::RefPtr<Gtk::Box> IComponentCommon::GetCommonTab()
{
    return Glib::RefPtr<Gtk::Box>();
}

Glib::RefPtr<Gtk::Window> IComponentCommon::CreateWindow()
{
}

};