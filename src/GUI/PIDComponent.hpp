#pragma once
#include "IComponentCommon.hpp"

namespace JSBEdit{

class PIDComponent : public IComponentCommon
{

public:
    PIDComponent(const std::string& name, ComponentType& type);
    ~PIDComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

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


    private:
    //Member vars
    void CreateCommonTab(Gtk::Notebook& note);

    Glib::RefPtr<Gtk::Window> m_window;
};

};