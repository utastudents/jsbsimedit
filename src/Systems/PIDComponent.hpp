#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class PIDComponent : public IComponentCommon
{

public:
    PIDComponent(const std::string& name);
    ~PIDComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    //================Tab1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
};

};