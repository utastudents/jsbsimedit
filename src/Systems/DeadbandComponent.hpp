#pragma once
#include "IComponentCommon.hpp"


namespace DragDrop{

class DeadbandComponent : public IComponentCommon
{
    public:
    DeadbandComponent(const std::string& name);
    ~DeadbandComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    // ==== TAB1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
};

};