#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class DeadbandComponent : public IComponentCommon
{
    public:
    DeadbandComponent(const std::string& name);
    ~DeadbandComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    // Constructors

    // ==== TAB1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    //====- TAB2

    float WIDTH{ 0.0f };
    float GAIN{ 0.0f };

    private:

    void CreateCommonTab(Gtk::Notebook& note);
    void SaveVariableChanges();
    void DeleteWidgetData();

    Glib::RefPtr<Gtk::Window> m_window;
    Glib::RefPtr<Gtk::Entry> m_widthEntry{};
    Glib::RefPtr<Gtk::Entry> m_gainEntry{};
    Glib::RefPtr<Gtk::Button> m_acceptButton{};
    Glib::RefPtr<Gtk::Button> m_cancelButton{};

};

};