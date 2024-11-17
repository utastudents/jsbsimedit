#pragma once
#include "IComponentCommon.hpp"

namespace DragDrop{

class SummerComponent : public IComponentCommon
{

public:
    SummerComponent(const std::string& name);
    ~SummerComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    //============= TAB1
    std::string Description {};
    std::string Input {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    float Bias { 0.0f };

    //Function
    void CreateCommonTab(Gtk::Notebook& note);
    void SaveVariableChanges();
    void DeleteWidgetData();

    void positiveToggled();
    void negativeToggled();
    void AddInput();
    void RemoveInput();

    //============TAB2
    std::vector<std::string> savedInput {};
    std::vector<std::string> listInput{};

    //Member Variables
    Glib::RefPtr<Gtk::Window> m_window;
    Glib::RefPtr<Gtk::Button> m_acceptButton{};
    Glib::RefPtr<Gtk::Button> m_cancelButton{};

    Glib::RefPtr<Gtk::CheckButton> m_positive{};
    Glib::RefPtr<Gtk::CheckButton> m_negative{};
    Glib::RefPtr<Gtk::Button> buttonAdd;
    Glib::RefPtr<Gtk::Button> buttonRemove;
    Glib::RefPtr<Gtk::TextBuffer> textBuffer;


 };

 };