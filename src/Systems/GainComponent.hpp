#pragma once
#include "IComponentCommon.hpp"
#include "GainComponentWindow.hpp"

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

private:

 };

 };