#pragma once
#include <gtkmm.h>
#include <string>
#include <iostream>
#include "ComponentTypeEnum.hpp"

class IComponentCommon
{
public:
    IComponentCommon(const std::string& compName, ComponentType& type);
    void CreateWindow();
    std::string GetName() const;
    ComponentType GetComponentType() const;
    void SetName(const std::string& newName);
    virtual void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) = 0;

protected:
    Glib::RefPtr<Gtk::Box> GetCommonTab();
    
    //Member Variables;
    std::string m_componentName {};
    ComponentType m_componentType;

private:
    void CreateComponentWindow();
    void CreateSourceDestWindow();

};