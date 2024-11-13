#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class GainComponent : public IComponentCommon
{

public:
    GainComponent(const std::string& name);
    ~GainComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    std::string Input {};
    bool IsTableEnabled = false;
    float Gain { 0.0f };
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };

private:
    //Member functions
    void CreateCommonTab(Gtk::Notebook& note);
    void HandleClipperLogic();
    void SaveVariableChanges();
    void DeleteWidgetData();

    //Member Variables
    Glib::RefPtr<Gtk::Window> m_window;
    Glib::RefPtr<Gtk::Entry> m_nameEntry{};
    Glib::RefPtr<Gtk::Entry> m_maxEntry{};
    Glib::RefPtr<Gtk::Entry> m_minEntry{};
    Glib::RefPtr<Gtk::CheckButton> m_clipperButton;
    Glib::RefPtr<Gtk::Button> m_acceptButton{};
    Glib::RefPtr<Gtk::Button> m_cancelButton{};

 };

 };