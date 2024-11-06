#pragma once
#include <gtkmm.h>
#include <string>
#include <iostream>
#include "ComponentTypeEnum.hpp"

namespace JSBEdit{

class IComponentCommon
{
public:
    IComponentCommon(const std::string& compName, ComponentType& type);
    std::string GetName() const;
    ComponentType GetComponentType() const;
    void SetName(const std::string& newName);
    virtual void LoadGUI(Glib::RefPtr<Gtk::Application>& app) = 0;

protected:
    Glib::RefPtr<Gtk::Window> CreateWindow();
    
    //Member Variables;
    std::string m_componentName {};
    ComponentType m_componentType;
    const static std::string COMMON_TAB;

private:
};

};