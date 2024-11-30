#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class DestinationComponent : public IComponentCommon
{

public:
    DestinationComponent(const std::string& name);
    ~DestinationComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;
    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    
    std::string propertyname {};
};

};