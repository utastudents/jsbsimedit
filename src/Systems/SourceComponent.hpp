#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class SourceComponent : public IComponentCommon
{

public:
    SourceComponent(const std::string& name, ComponentType& type);
    ~SourceComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    
    std::string propertyname {};
};

};