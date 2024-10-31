#pragma once
#include "IComponentCommon.hpp"

class PIDComponent : public IComponentCommon
{

public:
    PIDComponent(const std::string& name, ComponentType& type);
    ~PIDComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    float KP { 0.0f };
    float KI { 0.0f };
    float KD { 0.0f };
    std::string Trigger {};
    bool IsInputInverted = false;
};