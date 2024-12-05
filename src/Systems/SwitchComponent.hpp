#pragma once
#include "IComponentCommon.hpp"


namespace DragDrop{

class SwitchComponent : public IComponentCommon
{
    public:
    SwitchComponent(const std::string& name);
    ~SwitchComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    // ==== TAB1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
};

};