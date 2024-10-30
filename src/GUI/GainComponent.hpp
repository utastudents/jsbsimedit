#pragma once
#include "IComponentCommon.hpp"

class GainComponent : public IComponentCommon
{

public:
    GainComponent(const std::string& name, ComponentType& type);
    ~GainComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    std::string Input {};
    bool IsTableEnabled = false;
    std::string Gain{}//========update later...
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
 };