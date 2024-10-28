#include "IComponentCommon.hpp"

IComponentCommon::IComponentCommon(const std::string &compName, ComponentType& type)
    : m_componentName(compName), m_componentType(type)
{
}

//Potential circular dependancy here in the future..
void IComponentCommon::CreateWindow()
{
    if(m_componentType == ComponentType::DESTINATION || m_componentType == ComponentType::SOURCE)
        CreateSourceDestWindow();
    else
        CreateComponentWindow();
}

const std::string IComponentCommon::GetName() const
{
    return m_componentName;
}

const ComponentType IComponentCommon::GetComponentType() const
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

void IComponentCommon::CreateComponentWindow()
{
}

void IComponentCommon::CreateSourceDestWindow()
{
}
