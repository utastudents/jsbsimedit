#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class PIDComponent : public IComponentCommon
{

public:
    PIDComponent(const std::string& name);
    ~PIDComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    //================Tab1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    //================Tab2
    float KP { 0.0f };
    float KI { 0.0f };
    float KD { 0.0f };
    std::string Trigger {};
    bool InputInverted = false;


    private:
    //Member functions
    void CreateCommonTab(Gtk::Notebook& note);
    void SaveVariableChanges();
    void DeleteWidgetData();
    void HandleInvertLogic();

    //Member Variables
    Glib::RefPtr<Gtk::Window> m_window;
    Glib::RefPtr<Gtk::Entry> m_kpEntry{};
    Glib::RefPtr<Gtk::Entry> m_kiEntry{};
    Glib::RefPtr<Gtk::Entry> m_kdEntry{};
    Glib::RefPtr<Gtk::Entry> m_trigEntry{};
    Glib::RefPtr<Gtk::CheckButton> m_invertButton;
    Glib::RefPtr<Gtk::Button> m_acceptButton{};
    Glib::RefPtr<Gtk::Button> m_cancelButton{};
};

};