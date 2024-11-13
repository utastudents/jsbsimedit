#pragma once
#include "IComponentCommon.hpp"

namespace JSBEdit{

class DestinationComponent : public IComponentCommon
{

public:
    DestinationComponent(const std::string& name);
    ~DestinationComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    
    std::string propertyname {};
};

};