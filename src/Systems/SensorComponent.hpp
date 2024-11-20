#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class SensorComponent : public IComponentCommon
{

public:
    SensorComponent(const std::string& name);
    ~SensorComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    std::string Input{};
    float lag { 0.0f };
    bool IsNoiseEnabled = false;
    bool IsQuantizationEnabled = false;
    float Drift_Rate { 0.0f };
    float Bias { 0.0f };
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
};

};