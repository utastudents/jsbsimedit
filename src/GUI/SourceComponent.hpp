#pragma once
#include "IComponentCommon.hpp"

class SourceComponent : public IComponentCommon
{

public:
    SourceComponent(const std::string& name, ComponentType& type);
    ~SourceComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    
    std::string propertyname {};
};