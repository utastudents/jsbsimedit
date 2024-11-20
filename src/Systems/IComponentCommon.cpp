#include "IComponentCommon.hpp"

namespace DragDrop{

IComponentCommon::IComponentCommon(const std::string &compName, const ComponentType& type)
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

float IComponentCommon::GetClipperMax() const
{
    return m_clipperMax;
}
    
float IComponentCommon::GetClipperMin() const
{
    return m_clipperMin;
}

bool IComponentCommon::IsClipperEnabled() const
{
    return m_isClipperEnabled;
}

void IComponentCommon::SetClipperState(bool enable)
{
    m_isClipperEnabled = enable;
}

void IComponentCommon::SetClipperMax(float max)
{
    m_clipperMax = max;
}

void IComponentCommon::SetClipperMin(float min)
{
    m_clipperMin = min;
}

};