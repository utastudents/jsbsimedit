#pragma once
#include "IComponentCommon.hpp"
#include <vector>
#include <utility>

namespace DragDrop{

class KinematicsComponent : public IComponentCommon
{

public:
    KinematicsComponent(const std::string& name);
    ~KinematicsComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.



    //Function
    void CreateCommonTab(Gtk::Notebook& note);
    void SaveVariableChanges();
    void DeleteWidgetData();
    void HandleScaleLogic();

    // ========TAB1
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    bool IsInputInverted = false;

    // ========TAB2 
    std::vector<float> positionsHold{};  // Vector to store Entry widgets for positions
    std::vector<float> timesHold{};
    std::vector<std::pair<float, float>> table;
    bool IsInputScale = false;

    // Member Variables
    Glib::RefPtr<Gtk::Window> m_window;
    Glib::RefPtr<Gtk::Button> m_acceptButton{};
    Glib::RefPtr<Gtk::Button> m_cancelButton{};
    Glib::RefPtr<Gtk::CheckButton> m_scaleButton;

    Glib::RefPtr<Gtk::Entry> m_positionEntry{};
    Glib::RefPtr<Gtk::Entry> m_timeEntry{};

};

};