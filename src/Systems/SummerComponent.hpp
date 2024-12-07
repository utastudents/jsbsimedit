#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class SummerComponent : public IComponentCommon
{

public:
    SummerComponent(const std::string& name);
    ~SummerComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    //============= TAB1
    std::string Description {};
    std::string Input {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    float Bias { 0.0f };

 };

 };