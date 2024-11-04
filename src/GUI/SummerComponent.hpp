#pragma once
#include "IComponentCommon.hpp"

namespace JSBEdit{

class SummerComponent : public IComponentCommon
{

public:
    SummerComponent(const std::string& name, ComponentType& type);
    ~SummerComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    std::string Input {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    float Bias { 0.0f };
    bool IsInputInverted = false;
 };

 };