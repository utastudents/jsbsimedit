#pragma once
#include "IComponentCommon.hpp"

namespace JSBEdit{

class SourceComponent : public IComponentCommon
{

public:
    SourceComponent(const std::string& name, ComponentType& type);
    ~SourceComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    
    std::string propertyname {};
};

};